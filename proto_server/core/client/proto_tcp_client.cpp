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
                                           proto_net_pipeline& ps_pipeline/* = proto_net_empty_pipeline::empty_pipeline_inst*/,
                                           size_t buffer_size /*= 4096*/)
                : address_(address),  port_num_(port_num), socket_(proto_net_service_ref(ps_service_)),
                  ps_pipeline_(ps_pipeline),
                  buffer_size_(buffer_size),
                  buffer_(NULL)
        {
        }

        void
        proto_tcp_client::ps_run(void)
        {
            ps_service_->run();
        }

       void
       proto_tcp_client::ps_start(void)
       {
           ps_async_read();
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
        proto_tcp_client::ps_async_write(const char *data, size_t data_size)
        {
            if (data && data_size)
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(data, data_size),
                                         boost::bind(&proto_tcp_client::ps_handle_write, this,
                                                     boost::asio::placeholders::error));
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_client::ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred)
        {
            if (!error)
            {
                // handle a ps_read here
                proto_net_data req_data(buffer_, bytes_transferred);
                proto_net_data res_data;
                ps_pipeline_.ps_pipeline(req_data, res_data); // all of the magic takes place inside the ps_io_ object
                ps_async_write(res_data.data(), res_data.data_size()); // set response data ptr or size to zero for a non-write
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