
#ifndef PROTO_TCP_UPSTREAM_PIPELINE_HPP_
#define PROTO_TCP_UPSTREAM_PIPELINE_HPP_

//
//  proto_tcp_upstream_pipeline.hpp -
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/data/proto_net_pipeline.hpp>

namespace proto_net
{
    namespace data
    {
        // specialization of a pipeline used by clients for an upstream session
        class proto_tcp_upstream_pipeline : public proto_net_pipeline
        {
        public:

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);
            virtual void ps_pipe_in(proto_net_in_data& in_data);
            virtual void ps_pipe_out(proto_net_out_data& out_data);
        };
    }
}

#endif //PROTO_TCP_UPSTREAM_PIPELINE_HPP_
