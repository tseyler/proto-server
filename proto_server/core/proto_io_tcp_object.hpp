//
// Created by Terry Seyler on 10/19/15.
//

#ifndef PROTO_IO_TCP_OBJECT_HPP__
#define PROTO_IO_TCP_OBJECT_HPP__

#include <core/proto_io_object.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

namespace proto_net
{

    class proto_io_tcp_object : public proto_io_object
    {
    public:

        proto_io_tcp_object(unsigned short port_num = 80);
        virtual ~proto_io_tcp_object () {}

        // getters
        Proto_TCP_IO_Endpoint& ps_endpoint(void);
        Proto_Socket_TCP_Acceptor& ps_acceptor(void);

    protected:

        Proto_TCP_IO_Endpoint endpoint_;
        Proto_Socket_TCP_Acceptor acceptor_;
    };
}


#endif //PROTO_IO_TCP_OBJECT_HPP__
