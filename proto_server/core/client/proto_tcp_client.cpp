//
// Created by tseyler on 1/13/16.
//
#include <ostream>
#include <istream>
#include <boost/lexical_cast.hpp>
#include <core/client/proto_tcp_client.hpp>


namespace proto_net
{
    namespace client
    {
        proto_tcp_client::proto_tcp_client(const std::string& address,
                                           unsigned short port_num /* = 80*/, size_t buff_size /*= 4096 */)
                : address_(address),  port_num_(port_num), socket_(proto_net_service_ref(ps_service_)),
                  buff_size_(buff_size)
        {
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
            if (buff_size_ > msg.length())
            {
                char buf[buff_size_];
                memset(buf, 0, buff_size_);
                memcpy(buf, msg.c_str(), msg.length());

                boost::asio::write(socket_, boost::asio::buffer(buf, strlen(buf) + 1));
            }
        }

        std::string
        proto_tcp_client::ps_read_msg(void)
        {
            char buf[buff_size_];
            memset(buf, 0, buff_size_);
            boost::asio::streambuf b;
            if (boost::asio::read_until(socket_, b, '\0'))
            {
                std::istream is(&b);
                is.get(buf, buff_size_, '\0');
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