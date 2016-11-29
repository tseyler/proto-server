//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <ostream>
#include <istream>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <core/client/proto_tcp_client.hpp>


namespace proto_net
{
    namespace client
    {
        proto_tcp_client*
        proto_tcp_client::proto_tcp_client_cast(proto_service_ptr ps_ptr)
        {
            return dynamic_cast<proto_tcp_client*>(ps_ptr.get());
        }

        proto_async_io*
        proto_tcp_client::proto_async_io_cast(proto_service_ptr ps_ptr)
        {
            return dynamic_cast<proto_async_io*>(ps_ptr.get());
        }

        proto_tcp_client::proto_tcp_client(const std::string& address,
                                           unsigned short port_num /* = 80*/,
                                           proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                           size_t buffer_size /*= 4096*/)
                : address_(address),  port_num_(port_num), socket_(new proto_net_tcp_socket(proto_net_service_ref(ps_service_))),
                  resolver_(proto_net_service_ref(ps_service_)),
                  ps_pipeline_(ps_pipeline),
                  buffer_size_(buffer_size),
                  buffer_(NULL),
                  write_complete_(true),
                  max_wait_msec_(2000),
                  connected_(false)
        {
            buffer_ = buffer_size_ ? new char[buffer_size_] : NULL;
        }

        proto_tcp_client::proto_tcp_client(proto_net_service_ptr ps_service, const std::string& address,
        unsigned short port_num /*= 80*/,
                proto_net_pipeline& ps_pipeline /*= empty_pipeline_inst*/,
                size_t buffer_size /*= 4096*/)
                : proto_client(ps_service), address_(address),  port_num_(port_num),
                  socket_(new proto_net_tcp_socket(proto_net_service_ref(ps_service_))),
                  resolver_(proto_net_service_ref(ps_service_)),
                  ps_pipeline_(ps_pipeline),
                  buffer_size_(buffer_size),
                  buffer_(NULL),
                  write_complete_(true),
                  max_wait_msec_(2000),
                  connected_(false)
        {
            buffer_ = buffer_size_ ? new char[buffer_size_] : NULL;
        }

        proto_tcp_client::~proto_tcp_client()
        {
            delete [] buffer_;
        }

        void
        proto_tcp_client::ps_async_connect(const proto_net_in_data& write_data)
        {
            write_data_ = write_data;

            std::string port_str = boost::lexical_cast<std::string>(port_num_);
            proto_net_tcp_query query(address_.c_str(), port_str.c_str());
            resolver_.async_resolve(query, boost::bind(&proto_tcp_client::ps_handle_resolve, this,
                                                              boost::asio::placeholders::error,
                                                              boost::asio::placeholders::iterator));
        }

        void
        proto_tcp_client::ps_async_read(void)
        {
            socket_->async_read_some(boost::asio::buffer(buffer_, buffer_size_),
                                    boost::bind(&proto_tcp_client::ps_handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }

        void
        proto_tcp_client::ps_async_write(proto_net_in_data& data_in, bool no_write_complete /*= false*/)
        {
            if (data_in.data() && data_in.data_size()) //guard against empty data getting put into the pipe in
            {
                if (ps_write_complete(max_wait_msec_)) // previous write is complete
                {
                    ps_pipeline_.ps_pipe_in(data_in); // just prior to the write, execute the pipe_in
                    size_t data_size = data_in.data_size();
                    char* data = data_in.data();
                    if (data && data_size)
                    {
                        boost::asio::async_write(proto_net_tcp_socket_ref(socket_), boost::asio::buffer(data, data_size),
                                                 boost::bind(&proto_tcp_client::ps_handle_write, this,
                                                             boost::asio::placeholders::error,
                                                             boost::asio::placeholders::bytes_transferred));
                        write_complete_ = no_write_complete;
                    }
                    else
                        ps_async_read(); // just go back to reading
                }
                else
                    ps_async_read(); // just go back to reading
            }
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_client::ps_handle_resolve(const boost::system::error_code& error,
                                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
        {
            if (!error)
            {
                // Attempt a connection to the first endpoint in the list. Each endpoint
                // will be tried until we successfully establish a connection.
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_->async_connect(endpoint, boost::bind(&proto_tcp_client::ps_handle_connect, this,
                                                  boost::asio::placeholders::error, ++endpoint_iterator));
            }
            else
            {
                std::stringstream ss;
                ss << "proto_tcp_client::ps_handle_resolve - " << error.message();
                PROTO_LOG_ERROR( ss );
            }
        }

        void
        proto_tcp_client::ps_handle_connect(const boost::system::error_code& error,
                                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
        {
            if (!error)
            {
                connected_ = true;
                ps_async_write(write_data_);

                return;
            }

            connected_ = false;
            if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
            {

                // The connection failed. Try the next endpoint in the list.
                socket_->close();
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_->async_connect(endpoint, boost::bind(&proto_tcp_client::ps_handle_connect, this,
                                                  boost::asio::placeholders::error, ++endpoint_iterator));
            }

            // create a new instance for the next attempt to connect
            socket_ = proto_net_tcp_socket_ptr(new proto_net_tcp_socket(proto_net_service_ref(ps_service_)));
            std::stringstream ss;
            ss << "proto_tcp_client::ps_handle_connect - " << error.message();
            PROTO_LOG_ERROR( ss );

            proto_net_error_data err_data(ec_connect_error);
            ps_pipeline_.ps_pipe_error(err_data);
        }

        void
        proto_tcp_client::ps_handle_read(const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (!error)
            {
                // handle a ps_read here
                proto_net_data req_data;
                proto_net_data res_data(buffer_, bytes_transferred);
                if (res_data.data_size())
                {
                    ps_pipeline_.ps_pipeline(res_data, req_data); // response and request are reversed here
                    ps_pipeline_.ps_pipe_out(res_data); // post read, execute the pipe_out for the client
                }
                write_complete_ = true;

                ps_async_read(); // done go back to reading
            }
            else
            {
                proto_net_error_data err_data(ec_read_error);
                if (ps_pipeline_.ps_pipe_error(err_data))
                {
                    //delete this; // for now
                }
                else
                    ps_async_read(); // done go back to reading
            }
        }

        void
        proto_tcp_client::ps_handle_write(const boost::system::error_code &error, size_t /*bytes_transferred*/)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
            else
                delete this;
        }

        bool
        proto_tcp_client::ps_write_complete(size_t max_wait_msec /*= 2000*/)
        {
            const size_t sleep_msec = 50;

            size_t wait_msec(0);
            while (wait_msec < max_wait_msec)
            {
                if (write_complete_)
                    break;
                boost::this_thread::sleep(boost::posix_time::milliseconds(sleep_msec));
                wait_msec += sleep_msec;
            }

            return write_complete_;
        }

        size_t
        proto_tcp_client::ps_max_wait(void) const
        {
            return max_wait_msec_;
        }

        bool
        proto_tcp_client::ps_is_connected(void) const
        {
            return connected_;
        }

        // setter
        void
        proto_tcp_client::ps_max_wait(size_t max_wait_msec)
        {
            max_wait_msec_ = max_wait_msec;
        }

        proto_net_pipeline&
        proto_tcp_client::ps_pipeline(void)
        {
            return ps_pipeline_;
        }

        proto_net_tcp_socket_ptr
        proto_tcp_client::ps_socket(void)
        {
            return socket_;
        }
    }
}