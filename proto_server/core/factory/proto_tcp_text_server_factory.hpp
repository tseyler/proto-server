//
// Created by tseyler on 2/25/16.
//

#ifndef PROTO_TCP_TEXT_SERVER_FACTORY_HPP_
#define PROTO_TCP_TEXT_SERVER_FACTORY_HPP_

#include <core/factory/proto_service_factory.hpp>
#include <core/data/proto_net_pipeline.hpp>

namespace proto_net
{
    namespace factory
    {
        class proto_tcp_text_server_factory : public proto_service_factory
        {
        public:

            proto_tcp_text_server_factory(proto_net_pipeline& ps_pipeline, unsigned short port_num = 80,
                                          size_t buffer_size = 4096);


            proto_service_ptr ps_factory_create(bool start_on_creation);
            proto_service_ptr operator () (bool start_on_creation);
            proto_service_ptr operator () (void); // start_on_creation = true

        protected:

            proto_net_pipeline& ps_pipeline_;
            unsigned short port_num_;
            size_t buffer_size_;
        };

    }
}

#endif //PROTO_TCP_TEXT_SERVER_FACTORY_HPP_
