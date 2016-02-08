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

        void
        proto_server::ps_run(void)
        {
            ps_service_->run();
        }

        void
        proto_server::ps_stop(void)
        {
            ps_service_->stop();
        }
    }
}