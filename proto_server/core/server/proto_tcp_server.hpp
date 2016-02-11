//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_TCP_SERVER_HPP__
#define PROTO_TCP_SERVER_HPP__

#include <boost/shared_ptr.hpp>
#include <core/server/proto_server.hpp>
#include <core/server/proto_tcp_session.hpp>

using namespace boost::asio::ip;
using namespace proto_net;
using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_tcp_server : public proto_server
        {
        public:

            proto_tcp_server(unsigned short port_num = 80);
            virtual ~proto_tcp_server() {}

            // copy constructor
            proto_tcp_server(proto_tcp_server& ps);

            // pure virtuals
            virtual void ps_start_accept(proto_net_pipeline& ps_io, size_t buffer_size);

            unsigned short ps_port(void) const;

        protected:

            virtual void handle_accept(proto_tcp_session* session, const proto_net_error_code& error);

            unsigned short port_num_;
            proto_net_tcp_acceptor acceptor_;
        };
    }

}

#endif //PROTO_TCP_SERVER_HPP__