//
// Created by tseyler on 1/13/16.
//

#ifndef PROTO_TCP_CLIENT_HPP_
#define PROTO_TCP_CLIENT_HPP_

#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        class proto_tcp_client : public proto_client
        {
        public:

            proto_tcp_client(const std::string& address, unsigned short port_num = 80, size_t buff_size = 4096);

            // connect to a tcp server
            void ps_connect(void) throw(proto_net_error_code);

            // write a string
            void ps_write_msg(const std::string& msg);

            // read a string
            std::string ps_read_msg(void);

            // getter
            proto_net_tcp_socket& ps_socket(void);

        protected:

            std::string address_;
            unsigned short port_num_;
            proto_net_tcp_socket socket_;
            size_t buff_size_;
        };
    }
}


#endif //PROTO_TCP_CLIENT_HPP_
