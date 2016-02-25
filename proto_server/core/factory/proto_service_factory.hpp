//
// Created by tseyler on 2/24/16.
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
