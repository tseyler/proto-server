//
// Created by tseyler on 1/6/16.
//

#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        proto_client::proto_client() : ps_service_(new proto_net_service)
        {

        }

        proto_client::~proto_client()
        {

        }
    }
}