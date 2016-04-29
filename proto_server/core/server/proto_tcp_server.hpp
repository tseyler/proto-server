//
//  proto_tcp_server.hpp - base class for tcp servers
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_SERVER_HPP_
#define PROTO_TCP_SERVER_HPP_

#include <boost/shared_ptr.hpp>
#include <core/server/proto_server.hpp>
#include <core/server/proto_tcp_server_listener.hpp>

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

            static proto_tcp_server* proto_tcp_server_cast(proto_service_ptr ps_ptr);
            static proto_async_io* proto_async_io_cast(proto_service_ptr ps_ptr);

            proto_tcp_server(unsigned short port_num = 80);
            proto_tcp_server(proto_net_service_ptr ps_service, unsigned short port_num = 80);
            virtual ~proto_tcp_server() {}

            // copy constructor
            proto_tcp_server(proto_tcp_server& ps);

            // pure virtuals
            virtual void ps_start_accept(proto_net_pipeline& ps_pipeline, size_t buffer_size);

            unsigned short ps_port(void) const;

            virtual void ps_add_server_listener(proto_tcp_server_listener* listener);
            virtual void ps_remove_server_listener(proto_tcp_server_listener* listener);

        protected:

            virtual void handle_accept(proto_tcp_session* session, const proto_net_error_code& error);
            virtual void notify_server_listeners(proto_tcp_session* session);

            unsigned short port_num_;
            proto_net_tcp_acceptor acceptor_;
            proto_tcp_server_listener_vec listeners_;
        };
    }

}

#endif //PROTO_TCP_SERVER_HPP__