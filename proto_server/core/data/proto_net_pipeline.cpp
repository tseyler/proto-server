//
// Created by tseyler on 2/5/16.
//

#include <core/data/proto_net_pipeline.hpp>

namespace proto_net
{
    namespace data
    {
        proto_net_pipeline::proto_net_pipeline() : io_(NULL), ps_(NULL)
        {}

        proto_net_pipeline::~proto_net_pipeline()
        {}

        proto_service*
        proto_net_pipeline::ps_proto_service(void ) const
        {
            return ps_;
        }

        proto_async_io*
        proto_net_pipeline::ps_proto_io(void) const
        {
            return io_;
        }

        void
        proto_net_pipeline::ps_proto_service(proto_service* ps)
        {
            ps_ = ps;
        }

        void
        proto_net_pipeline::ps_proto_io(proto_async_io* io)
        {
            io_ = io;
        }

        proto_net_empty_pipeline empty_pipeline_inst {};

    }
}

