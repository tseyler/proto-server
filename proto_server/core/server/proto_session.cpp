//
// Created by Terry Seyler on 10/27/15.
//

#include <core/server/proto_session.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        proto_session::proto_session(proto_net_pipeline& ps_pipeline, size_t buffer_size /* = 4096*/) :
                ps_pipeline_(ps_pipeline),
                buffer_size_(buffer_size),
                buffer_(NULL)
        {

            buffer_ = buffer_size_ ? new char[buffer_size_] : NULL;
        }

        proto_session::~proto_session()
        {
            delete [] buffer_;
        }


        const char*
        proto_session::ps_buffer(void) const
        {
            return buffer_;
        }

        size_t
        proto_session::ps_buffer_size(void) const
        {
            return buffer_size_;
        }

        proto_net_pipeline&
        proto_session::ps_pipeline(void)
        {
            return ps_pipeline_;
        }

        proto_net_client_pipeline::proto_net_client_pipeline(proto_session* us_session /*= NULL */) :
                us_session_(us_session)
        {}

        proto_net_client_pipeline::~proto_net_client_pipeline()
        {}

        void
        proto_net_client_pipeline::ps_proto_session(proto_session* us_session)
        {

        }

        void
        proto_net_client_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
        {

        }

        void
        proto_net_client_pipeline::ps_pipe_in(proto_net_in_data& in_data)
        {

        }

        void
        proto_net_client_pipeline::ps_pipe_out(proto_net_out_data& out_data)
        {
            if (us_session_)
                us_session_->ps_async_write(out_data);
        }

    }
}

