//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_TCP_SERVER_HPP__
#define PROTO_TCP_SERVER_HPP__

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

            proto_tcp_server(proto_net_service& io_service, unsigned short port_num = 80);
            virtual ~proto_tcp_server() {}

            // copy constructor
           // proto_tcp_server(const proto_tcp_server& ps);
           // proto_tcp_server& clone(const proto_tcp_server& ps);
            //proto_tcp_server& operator =(const proto_tcp_server& ps);

            // pure virtuals
            virtual void ps_run(void);
            virtual void ps_start_accept(proto_net_io& ps_io, size_t buffer_size);

        protected:

            virtual void handle_accept(proto_tcp_session* session, const boost::system::error_code& error);

            proto_net_service& io_service_;
		    tcp::acceptor acceptor_;
        };
    }

}

#endif //PROTO_TCP_SERVER_HPP__