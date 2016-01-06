//
// Created by tseyler on 1/6/16.
//

#include <core/server/proto_server.hpp>

namespace proto_net
{
    namespace server
    {
        proto_server::proto_server() : ps_service_(new proto_net_service)
        {

        }

        proto_server::~proto_server()
        {

        }
    }
}