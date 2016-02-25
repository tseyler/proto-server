//
// Created by tseyler on 2/24/16.
//

#include <core/factory/proto_tcp_text_client_factory.hpp>
#include <core/client/proto_tcp_text_client.hpp>

namespace proto_net
{
    using namespace client;

    namespace factory
    {
        proto_tcp_text_client_factory::proto_tcp_text_client_factory(const std::string& address, unsigned short port_num /* = 80*/,
                                      proto_net_pipeline& ps_pipeline /*= empty_pipeline_inst*/,
                                      size_t buffer_size /* = 4096 */) : address_(address), connect_data_(""), port_num_(port_num),
                                                                         ps_pipeline_(ps_pipeline), buffer_size_(buffer_size)
        { }

        proto_tcp_text_client_factory::proto_tcp_text_client_factory(const std::string& address, const proto_net_in_data& connect_data,
                                      unsigned short port_num /*= 80*/,
                                      proto_net_pipeline& ps_pipeline /*= empty_pipeline_inst*/,
                                      size_t buffer_size /*= 4096*/) : address_(address), connect_data_(connect_data),
                                                                       port_num_(port_num), ps_pipeline_(ps_pipeline),
                                                                       buffer_size_(buffer_size)
        { }

        proto_service_ptr
        proto_tcp_text_client_factory::ps_factory_create(bool start_on_creation)
        {
            proto_service_ptr ps_ptr(new proto_tcp_text_client(address_, port_num_, ps_pipeline_, buffer_size_));

            proto_tcp_text_client* client_ptr = proto_tcp_text_client::proto_tcp_text_client_cast(ps_ptr); //dynamic_cast<proto_tcp_text_client*>(ps_ptr.get());
            if (client_ptr)
                client_ptr->ps_async_connect(connect_data_);
            // start the client service
            if (start_on_creation)
                ps_ptr->ps_start();

            return ps_ptr;
        }

        proto_service_ptr
        proto_tcp_text_client_factory::operator () (bool start_on_creation)
        {
            return ps_factory_create(start_on_creation);
        }

        proto_service_ptr
        proto_tcp_text_client_factory::operator () (void) // start_on_creation = true
        {
            return ps_factory_create(true);
        }
    }
}
