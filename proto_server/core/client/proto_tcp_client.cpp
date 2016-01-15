//
// Created by tseyler on 1/13/16.
//

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

        proto_net_tcp_socket&
        proto_tcp_client::ps_socket(void)
        {
            return socket_;
        }
    }
}