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

        static tcp ps_internet_protocol(int af_protocol_family);

        typedef shared_ptr<proto_io_object<tcp> > Proto_TCP_IO_Object;

        proto_tcp_server();
        proto_tcp_server(int protocol_family, unsigned short port_num);
        // copy constructor
        proto_tcp_server(const proto_tcp_server& ps);

        virtual ~proto_tcp_server() {}

        proto_tcp_server& clone(const proto_tcp_server& ps);

        proto_tcp_server& operator =(const proto_tcp_server& ps);

        // pure virtuals
        virtual void ps_initialize(void);
        virtual void ps_run(void);

    protected:

        virtual void ps_start_accept(void);

        //virtual void handle_accept(http_session* session,
                                  // const boost::system::error_code& error);

    };
}

#endif //PROTO_TCP_SERVER_HPP__