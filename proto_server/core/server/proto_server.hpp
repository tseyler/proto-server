//
//  proto_server.hpp - base class for servers
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SERVER_HPP_
#define PROTO_SERVER_HPP_

#include <core/proto_net_types.hpp>
#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_server : public proto_service
        {
        public:

            proto_server();
            proto_server(proto_net_service_ptr ps_service);

            virtual ~proto_server();

            // pure virtuals
            virtual void ps_run(void);
            virtual void ps_start(void);
            virtual void ps_stop(void);
            virtual void ps_start_accept(proto_net_pipeline& ps_pipeline, size_t buffer_size) = 0;

        protected:

            proto_net_service_ptr ps_service_;
            proto_net_thread_ptr ps_thread_;
        };

    }
}

#endif //PROTO_SERVER_HPP_

