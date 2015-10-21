//
// Created by Terry Seyler on 8/30/15.
//

#ifndef PROTO_TCP_SESSION_HPP__
#define PROTO_TCP_SESSION_HPP__

#include <core/proto_io_tcp_object.hpp>
#include <core/server/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {
        class proto_tcp_session
        {
        public:

            proto_tcp_session(proto_io_tcp_object& tcp_io_object);
            virtual ~proto_tcp_session();

        protected:

            tcp::socket socket_;

        };
    }

}

#endif
