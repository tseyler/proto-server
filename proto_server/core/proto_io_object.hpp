//
// Created by Terry Seyler on 8/21/15.
//

#ifndef PROTO_IO_OBJECT_HPP__
#define PROTO_IO_OBJECT_HPP__

#include <boost/asio.hpp>

#include <core/proto_constants.h>

using namespace boost::asio;
using namespace boost::asio::ip;

namespace proto_net
{

    typedef basic_endpoint<tcp> Proto_TCP_IO_Endpoint;
    typedef basic_socket_acceptor<tcp> Proto_Socket_TCP_Acceptor;

    class proto_io_object
    {
    public:

        proto_io_object(unsigned short port_num = 80);
        virtual ~proto_io_object() {}

        // getters
        io_service& ps_io_service(void);
        unsigned short ps_io_port_num(void) const;

    protected:

        io_service io_service_;
        unsigned short port_num_;
    };

}

#endif

