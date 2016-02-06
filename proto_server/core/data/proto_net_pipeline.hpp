//
// Created by Terry Seyler on 10/25/15.
//

#ifndef PROTO_NET_PIPELINE_HPP_
#define PROTO_NET_PIPELINE_HPP_

#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_pipeline
        {
        public:

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) = 0;  // the response data
            virtual void ps_pipe_in(proto_net_in_data& in_data) = 0;
            virtual void ps_pipe_out(proto_net_out_data& out_data) = 0;
        };

        // specialization with empty implementation
        class proto_net_empty_pipeline : public proto_net_pipeline
        {
        public:

            void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) {} // empty
            void ps_pipe_in(proto_net_in_data& in_data) {}
            void ps_pipe_out(proto_net_out_data& out_data) {}
        };


        extern proto_net_empty_pipeline empty_pipeline_inst;
    }
}
#endif //PROTO_NET_PIPELINE_HPP_
