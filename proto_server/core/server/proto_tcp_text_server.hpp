//
// Created by tseyler on 2/10/16.
//

#ifndef PROTO_TCP_TEXT_SERVER_HPP_
#define PROTO_TCP_TEXT_SERVER_HPP_

#include <core/server/proto_tcp_server.hpp>
#include <core/server/proto_tcp_text_session.hpp>

using namespace boost::asio::ip;
using namespace proto_net;
using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_tcp_text_server : public proto_tcp_server
        {
        public:

            static proto_tcp_text_server* proto_tcp_text_server_cast(proto_service_ptr ps_ptr);

            proto_tcp_text_server(unsigned short port_num = 80);
            proto_tcp_text_server(proto_net_service_ptr ps_service, unsigned short port_num = 80);
            virtual ~proto_tcp_text_server() {}

            // copy constructor
            proto_tcp_text_server(proto_tcp_text_server& ps);

            // pure virtuals
            virtual void ps_start_accept(proto_net_pipeline& ps_io, size_t buffer_size);

        protected:

            virtual void handle_accept(proto_tcp_text_session* session, const proto_net_error_code& error);
        };
    }
}
#endif //PROTO_TCP_TEXT_SERVER_HPP_
