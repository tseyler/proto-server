

#include <core/data/proto_tcp_upstream_pipeline.hpp>

namespace proto_net
{
    namespace data
    {
        void
        proto_tcp_upstream_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
        {
            // empty
        }

        void
        proto_tcp_upstream_pipeline::ps_pipe_in(proto_net_in_data& in_data)
        {
            // empty
        }

        void
        proto_tcp_upstream_pipeline::ps_pipe_out(proto_net_out_data& out_data)
        {
            if (io_)
                io_->ps_async_write(out_data); // this sends the data upstream
        }
    }
}

