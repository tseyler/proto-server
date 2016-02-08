//
// Created by Terry Seyler on 10/27/15.
//

#ifndef PROTO_SESSION_HPP_
#define PROTO_SESSION_HPP_

#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_session
        {
        public:

            proto_session(proto_net_pipeline& ps_pipeline = empty_pipeline_inst, size_t buffer_size = 4096);
            virtual ~proto_session();

            virtual void ps_start(void) = 0;
            virtual void ps_async_read(void) = 0;
            virtual void ps_async_write(const proto_net_in_data& data_in) = 0;

            // getters
            const char* ps_buffer(void) const;
            size_t ps_buffer_size(void) const;
            proto_net_pipeline& ps_pipeline(void);

        protected:

            proto_net_pipeline& ps_pipeline_;
            size_t buffer_size_;
            char* buffer_;

        };
    }
}

#endif //PROTO_SESSION_HPP_
