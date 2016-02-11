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

        proto_net_server_pipeline::proto_net_server_pipeline(proto_net::client::proto_client* ds_client /* = NULL*/) :
                ds_client_(ds_client)
        {
        }

        proto_net_server_pipeline::~proto_net_server_pipeline()
        {}

        void
        proto_net_server_pipeline::ps_proto_client(proto_client* ds_client)
        {
            ds_client_ = ds_client;
        }

        void
        proto_net_server_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
        {
            // empty
        }

        void
        proto_net_server_pipeline::ps_pipe_in(proto_net_in_data& in_data)
        {
//            if (ds_client_)
//                ds_client_->ps_async_write(in_data);
        }

        void
        proto_net_server_pipeline::ps_pipe_out(proto_net_out_data& out_data)
        {

        }
    }
}