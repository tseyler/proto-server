//
//  proto_tcp_client_factory.hpp - factory for tcp clients
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_CLIENT_FACTORY_HPP_
#define PROTO_TCP_CLIENT_FACTORY_HPP_

#include <core/factory/proto_service_factory.hpp>
#include <core/data/proto_net_pipeline.hpp>
#include <core/client/proto_tcp_client.hpp>

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
