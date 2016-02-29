//
//  proto_client.hpp - base class for clients
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
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
            virtual void ps_start(void);
            virtual void ps_stop(void);

        protected:

            proto_net_service_ptr ps_service_;
            proto_net_thread_ptr ps_thread_;
        };
    }
}


#endif //PROTO_CLIENT_HPP_
