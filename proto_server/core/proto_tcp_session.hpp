//
// Created by Terry Seyler on 8/30/15.
//

#ifndef PROTO_TCP_SESSION_HPP__
#define PROTO_TCP_SESSION_HPP__

#include <core/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{

    class proto_tcp_session
    {
    public:

        proto_tcp_session(proto_tcp_server::Proto_TCP_IO_Object& tcp_io_object);
        virtual ~proto_tcp_session();

    protected:

        tcp::socket socket_;

    };
}

#endif
