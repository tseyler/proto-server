//
// Created by tseyler on 1/13/16.
//

#ifndef PROTO_TCP_CLIENT_HPP__
#define PROTO_TCP_CLIENT_HPP__

#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        class proto_tcp_client : public proto_client
        {
        public:

            proto_tcp_client(const std::string& address, unsigned short port_num = 80);
            virtual ~proto_tcp_client() {}

        protected:

            std::string address_;
            unsigned short port_num_;
        };
    }
}


#endif //PROTO_TCP_CLIENT_HPP__
