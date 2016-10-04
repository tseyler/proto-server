//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/factory/proto_tcp_text_client_factory.hpp>

namespace proto_net
{
    using namespace client;

    namespace factory
    {
        proto_tcp_text_client_factory::proto_tcp_text_client_factory(const std::string& address, unsigned short port_num /* = 80*/,
                                      proto_net_pipeline& ps_pipeline /*= empty_pipeline_inst*/,
                                      size_t buffer_size /* = 4096 */) :
                proto_tcp_client_factory(address, port_num, ps_pipeline, buffer_size)
        { }

        proto_tcp_text_client_factory::proto_tcp_text_client_factory(const std::string& address, const proto_net_in_data& connect_data,
                                      unsigned short port_num /*= 80*/,
                                      proto_net_pipeline& ps_pipeline /*= empty_pipeline_inst*/,
                                      size_t buffer_size /*= 4096*/) :
                proto_tcp_client_factory(address, connect_data, port_num, ps_pipeline, buffer_size)
        { }

        proto_service_ptr
        proto_tcp_text_client_factory::ps_factory_create(bool start_on_creation)
        {
            proto_service_ptr ps_ptr(new proto_tcp_text_client(address_, port_num_, ps_pipeline_, buffer_size_));
            proto_tcp_text_client* client_ptr = proto_tcp_text_client::proto_tcp_text_client_cast(ps_ptr);
            if (client_ptr)
                client_ptr->ps_async_connect(connect_data_);
            // start the client service
            if (start_on_creation)
                ps_ptr->ps_start();

            return ps_ptr;
        }
    }
}
