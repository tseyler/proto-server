//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/data/proto_tcp_downstream_pipeline.hpp>

namespace proto_net
{
    namespace data
    {

        proto_tcp_downstream_pipeline::proto_tcp_downstream_pipeline() : proto_net_pipeline()
        {}

        proto_tcp_downstream_pipeline::~proto_tcp_downstream_pipeline()
        {}

        void
        proto_tcp_downstream_pipeline::ps_pipeline(const proto_net_in_data& /*req_data*/, proto_net_out_data& /*res_data*/)
        {
            // empty
        }

        void
        proto_tcp_downstream_pipeline::ps_pipe_in(proto_net_in_data& in_data)
        {
            if (io_)
                io_->ps_async_write(in_data, false); // here is how we forward the message downstream
        }

        void
        proto_tcp_downstream_pipeline::ps_pipe_out(proto_net_out_data& /*out_data*/)
        {
            // empty
        }

        bool proto_tcp_downstream_pipeline::ps_pipe_error(proto_net_error_data& /*error_data*/)
        {
            return false;
        }
    }
}
