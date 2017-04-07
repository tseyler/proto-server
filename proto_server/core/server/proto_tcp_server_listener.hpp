//
//  proto_tcp_server_listener.hpp - base class for server listeners
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_SERVER_LISTENER_HPP_
#define PROTO_TCP_SERVER_LISTENER_HPP_

#include <vector>
#include <core/server/proto_tcp_session.hpp>

namespace proto_net
{
    namespace server
    {
        class proto_tcp_server_listener
        {
        public:

            // returns true if a change has occurred
            virtual bool ps_on_new_tcp_session(proto_tcp_session *session) = 0;

        };

        typedef std::vector<proto_tcp_server_listener*> proto_tcp_server_listener_vec;
        typedef proto_tcp_server_listener_vec::iterator proto_tcp_server_listener_vec_iterator;
    }
}
#endif //PROTO_TCP_SERVER_LISTENER_HPP_
