//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_TCP_SERVER_HPP__
#define PROTO_TCP_SERVER_HPP__

#include <core/proto_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    class proto_tcp_server : public proto_server<tcp>
    {
    public:

        proto_tcp_server();
        proto_tcp_server(int protocol_family, unsigned short port_num);
        // copy constructor
        proto_tcp_server(const proto_tcp_server& ps);

        virtual ~proto_tcp_server() {}

        proto_tcp_server& clone(const proto_tcp_server& ps);

        proto_tcp_server& operator =(const proto_tcp_server& ps);

        // pure virtual
        virtual tcp ps_internet_protocol(void) const;

    protected:

    };
}

#endif //PROTO_TCP_SERVER_HPP__