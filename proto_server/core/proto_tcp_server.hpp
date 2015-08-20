//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_TCP_SERVER_HPP__
#define PROTO_TCP_SERVER_HPP__

#include <core/proto_server.hpp>

namespace proto_net
{
    class proto_tcp_server : public proto_server<boost::asio::ip::tcp>
    {
    public:

        proto_tcp_server();
        virtual ~proto_tcp_server() {}

    protected:

    };
}

#endif //PROTO_TCP_SERVER_HPP__