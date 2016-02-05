//
// Created by tseyler on 1/6/16.
//

#ifndef PROTO_CLIENT_HPP_
#define PROTO_CLIENT_HPP_

#include <core/proto_net_types.hpp>
#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace client
    {
        class proto_client
        {
        public:

            proto_client();

            virtual ~proto_client();

            // pure virtuals
            virtual void ps_run(void) = 0;
            virtual void ps_start(void) = 0;
            virtual void ps_async_read(void) = 0;
            virtual void ps_async_write(const char *data, size_t data_size) = 0;

        protected:

            proto_net_service_ptr ps_service_;
        };
    }
}


#endif //PROTO_CLIENT_HPP_
