//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_SERVER_HPP__
#define PROTO_SERVER_HPP__


#include <core/proto_net_types.hpp>
#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_server
        {
        public:

            proto_server();

            virtual ~proto_server();

            // pure virtuals
            virtual void ps_run(void) = 0;
            virtual void ps_start_accept(proto_net_pipeline& ps_pipeline, size_t buffer_size) = 0;

        protected:

            proto_net_service_ptr ps_service_;
        };
    }
}

#endif //PROTO_SERVER_HPP__

