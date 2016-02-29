//
//  proto_service_factory.hpp - interface for factories
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SERVICE_FACTORY_HPP_
#define PROTO_SERVICE_FACTORY_HPP_

#include <core/proto_service.hpp>

namespace proto_net
{
    namespace factory
    {
        class proto_service_factory
        {
        public:

            virtual proto_service_ptr ps_factory_create(bool start_on_creation) = 0;
        };

    }
}

#endif //PROTO_SERVICE_FACTORY_HPP_
