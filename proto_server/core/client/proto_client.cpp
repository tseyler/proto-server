//
// Created by tseyler on 1/6/16.
//

#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        proto_client::proto_client() : ps_service_(new proto_net_service)
        {}

        proto_client::proto_client(proto_net_service_ptr ps_service) : ps_service_(ps_service)
        {}

        proto_client::~proto_client()
        {}

        void
        proto_client::ps_run(void)
        {
            ps_service_->run();
        }

        void
        proto_client::ps_stop(void)
        {
            ps_service_->stop();
        }
    }
}