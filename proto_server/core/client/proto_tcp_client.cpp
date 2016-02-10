//
// Created by tseyler on 1/13/16.
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
        proto_tcp_client::proto_tcp_client(const std::string& address,
                                           unsigned short port_num /* = 80*/,
                                           proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                           size_t buffer_size /*= 4096*/)
                : address_(address),  port_num_(port_num), socket_(proto_net_service_ref(ps_service_)),
                  resolver_(proto_net_service_ref(ps_service_)),
                  ps_pipeline_(ps_pipeline),
                  buffer_size_(buffer_size),
                  buffer_(NULL),
                  write_data_()
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
            socket_.async_read_some(boost::asio::buffer(buffer_, buffer_size_),
                                    boost::bind(&proto_tcp_client::ps_handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }

        void
        proto_tcp_client::ps_async_write(proto_net_in_data& data_in)
        {
            ps_pipeline_.ps_pipe_in(data_in); // just prior to the write, execute the pipe_in
            proto_net_data_type dt = data_in.data_type();
            char* data = data_in.data();
            size_t data_size = data_in.data_size();
            if (dt == data_text)
                data_size++;    // add a null character for null terminated strings
            if (data && data_size)
                boost::asio::async_write(socket_, boost::asio::buffer(data, data_size),
                                         boost::bind(&proto_tcp_client::ps_handle_write, this,
                                                     boost::asio::placeholders::error));
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
                socket_.async_connect(endpoint, boost::bind(&proto_tcp_client::ps_handle_connect, this,
                                                  boost::asio::placeholders::error, ++endpoint_iterator));
            }
            else
            {
                std::cout << "Error: " << error.message() << std::endl;
            }
        }

        void
        proto_tcp_client::ps_handle_connect(const boost::system::error_code& error,
                                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
        {
            if (!error)
            {
                ps_async_write(write_data_);
            }
            else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
            {
                // The connection failed. Try the next endpoint in the list.
                socket_.close();
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint, boost::bind(&proto_tcp_client::ps_handle_connect, this,
                                                  boost::asio::placeholders::error, ++endpoint_iterator));
            }
            else
            {
                std::cout << "Error: " << error.message() << std::endl;
            }
        }

        void
        proto_tcp_client::ps_handle_read(const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (!error)
            {
                // handle a ps_read here
                proto_net_data req_data;
                proto_net_data res_data(buffer_, bytes_transferred);
                ps_pipeline_.ps_pipeline(res_data, req_data); // response and request are reversed here
                ps_pipeline_.ps_pipe_out(res_data); // post read, execute the pipe_out for the client
                ps_async_write(req_data);
            }
            else
                delete this; // for now
        }

        void
        proto_tcp_client::ps_handle_write(const boost::system::error_code &error)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
            else
                delete this;
        }

        void
        proto_tcp_client::ps_connect(void) throw(proto_net_error_code)
        {
            proto_net_tcp_resolver resolver(proto_net_service_ref(ps_service_));
            std::string port_str = boost::lexical_cast<std::string>(port_num_);
            proto_net_tcp_query query(address_.c_str(), port_str.c_str());
            proto_net_tcp_iterator iterator = ps_tcp_resolve(resolver, query);

            ps_tcp_connect(socket_, iterator);
        }

        void
        proto_tcp_client::ps_write_msg(const std::string& msg)
        {
            if (buffer_size_ > msg.length())
            {
                char buf[buffer_size_];
                memset(buf, 0, buffer_size_);
                memcpy(buf, msg.c_str(), msg.length());

                boost::asio::write(socket_, boost::asio::buffer(buf, strlen(buf) + 1));
            }
        }

        std::string
        proto_tcp_client::ps_read_msg(void)
        {
            char buf[buffer_size_];
            memset(buf, 0, buffer_size_);
            boost::asio::streambuf b;
            if (boost::asio::read_until(socket_, b, '\0'))
            {
                std::istream is(&b);
                is.get(buf, buffer_size_, '\0');
            }

            return std::string(buf);
        }

        proto_net_tcp_socket&
        proto_tcp_client::ps_socket(void)
        {
            return socket_;
        }
    }
}