//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/factory/proto_tcp_server_factory.hpp>
#include <core/server/proto_tcp_server.hpp>

namespace proto_net
{
    using namespace server;

    namespace factory
    {

        proto_tcp_server_factory::proto_tcp_server_factory(proto_net_pipeline& ps_pipeline, unsigned short port_num /*= 80*/,
                                                                     size_t buffer_size /*= 4096*/) :
                ps_pipeline_(ps_pipeline), port_num_(port_num), buffer_size_(buffer_size)
        { }


        proto_service_ptr
        proto_tcp_server_factory::ps_factory_create(bool start_on_creation)
        {
            proto_service_ptr ps_ptr(new proto_tcp_server(port_num_));

            proto_tcp_server* server_ptr = dynamic_cast<proto_tcp_server*>(ps_ptr.get());
            if (server_ptr)
                server_ptr->ps_start_accept(ps_pipeline_, buffer_size_);

            // start the server service
            if (start_on_creation)
                ps_ptr->ps_start();

            return ps_ptr;
        }

        proto_service_ptr
        proto_tcp_server_factory::operator()(bool start_on_creation)
        {
            return ps_factory_create(start_on_creation);
        }

        proto_service_ptr
        proto_tcp_server_factory::operator()(void) // start_on_creation = true
        {
            return ps_factory_create(true);
        }
    }
}
