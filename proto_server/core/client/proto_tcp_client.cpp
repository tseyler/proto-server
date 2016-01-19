//
// Created by tseyler on 1/13/16.
//
#include <ostream>
#include <istream>
#include <boost/lexical_cast.hpp>
#include "proto_tcp_client.hpp"


namespace proto_net
{
    namespace client
    {

        proto_tcp_client::proto_tcp_client(const std::string& address, unsigned short port_num /* = 80*/)
                : address_(address),  port_num_(port_num), socket_(proto_net_service_ref(ps_service_))
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
        proto_tcp_client::ps_write_string(const std::string& buff)
        {
            boost::asio::streambuf request;
            std::ostream request_stream(&request);
            request_stream << buff;

            boost::asio::write(socket_, request);
        }

        std::string
        proto_tcp_client::ps_read_string(const char* read_delim)
        {
            boost::asio::streambuf response;
            boost::asio::read_until(socket_, response, read_delim);
            std::istream response_stream(&response);
            std::string read_response;
            response_stream >> read_response;

            return read_response;
        }

        proto_net_tcp_socket&
        proto_tcp_client::ps_socket(void)
        {
            return socket_;
        }
    }
}