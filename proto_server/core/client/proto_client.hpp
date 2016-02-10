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
        class proto_client : public proto_service
        {
        public:

            proto_client();

            virtual ~proto_client();

            // pure virtuals
            virtual void ps_run(void);
            virtual void ps_stop(void);
            virtual void ps_async_read(void) = 0;
            virtual void ps_async_write(proto_net_in_data& data_in) = 0;

        protected:

            proto_net_service_ptr ps_service_;
        };

        // specialization of a pipeline used by servers for a downstream client
        class proto_net_server_pipeline : public proto_net_pipeline
        {
        public:

            proto_net_server_pipeline(proto_client* ds_client = NULL);
            virtual ~proto_net_server_pipeline();

            virtual void ps_proto_client(proto_client* ds_client);

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);
            virtual void ps_pipe_in(proto_net_in_data& in_data);
            virtual void ps_pipe_out(proto_net_out_data& out_data);

        protected:

            proto_client* ds_client_;
        };
    }
}


#endif //PROTO_CLIENT_HPP_
