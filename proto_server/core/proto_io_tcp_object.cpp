//
// Created by Terry Seyler on 10/19/15.
//


#include <core/proto_io_tcp_object.hpp>

using namespace boost::asio::ip;

namespace proto_net
{

    proto_io_tcp_object::proto_io_tcp_object(unsigned short port_num /*= 80*/) : proto_io_object(port_num),
                                                                                 endpoint_(tcp::v4(), port_num),
                                                                                 acceptor_(io_service_, endpoint_, port_num)
    { }

    Proto_TCP_IO_Endpoint&
    proto_io_tcp_object::ps_endpoint(void)
    {
        return endpoint_;
    }


    Proto_Socket_TCP_Acceptor&
    proto_io_tcp_object::ps_acceptor(void)
    {
        return acceptor_;
    }

}

