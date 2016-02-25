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
                                      size_t buffer_size /* = 4096 */) : address_(address), port_num_(port_num),
                                                                         ps_pipeline_(ps_pipeline), buffer_size_(buffer_size)
        { }

        proto_service_ptr
        proto_tcp_text_client_factory::ps_factory_create(bool start_on_creation /* = true */)
        {
            proto_service_ptr ps_ptr(new proto_tcp_text_client(address_, port_num_, ps_pipeline_, buffer_size_));

            return ps_ptr;
        }

        proto_service_ptr
        proto_tcp_text_client_factory::operator () (bool start_on_creation /*= true */)
        {
            return ps_factory_create(start_on_creation);
        }
    }
}
