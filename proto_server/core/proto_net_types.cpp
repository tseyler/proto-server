//
// Created by tseyler on 1/5/16.
//

#include <core/proto_net_types.hpp>

namespace proto_net
{

    proto_net_service& proto_net_service_ref(proto_net_service_ptr ptr)
    {
        return *ptr.get();
    }
}
