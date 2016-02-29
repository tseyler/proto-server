//
// Created by tseyler on 2/24/16.
//

#ifndef PROTO_TCP_CLIENT_FACTORY_HPP_
#define PROTO_TCP_CLIENT_FACTORY_HPP_

#include <core/factory/proto_service_factory.hpp>
#include <core/data/proto_net_pipeline.hpp>

namespace proto_net
{
    namespace factory
    {
        class proto_tcp_client_factory : public proto_service_factory
        {
        public:

            proto_tcp_client_factory(const std::string& address,
                                          unsigned short port_num = 80,
                                          proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                                          size_t buffer_size = 4096);

            proto_tcp_client_factory(const std::string& address, const proto_net_in_data& connect_data,
                                          unsigned short port_num = 80,
                                          proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                                          size_t buffer_size = 4096);

            virtual proto_service_ptr ps_factory_create(bool start_on_creation);
            virtual proto_service_ptr operator () (bool start_on_creation);
            virtual proto_service_ptr operator () (void); // start_on_creation = true

        protected:

            std::string address_;
            proto_net_in_data connect_data_;
            unsigned short port_num_;
            proto_net_pipeline& ps_pipeline_;
            size_t buffer_size_;
        };

    }
}

#endif //PROTO_TCP_CLIENT_FACTORY_HPP_
