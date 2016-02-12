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
            proto_client(proto_net_service_ptr ps_service);
            virtual ~proto_client();

            virtual void ps_run(void);
            virtual void ps_stop(void);

        protected:

            proto_net_service_ptr ps_service_;
        };
    }
}


#endif //PROTO_CLIENT_HPP_
