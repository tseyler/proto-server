//
// Created by tseyler on 1/6/16.
//

#ifndef PROTO_CLIENT_HPP__
#define PROTO_CLIENT_HPP__

#include <core/proto_net_types.hpp>
#include <core/data/proto_net_io.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace client
    {
        class proto_client
        {
        public:

            proto_client();

            virtual ~proto_client();


        protected:

            proto_net_service_ptr ps_service_;
        };
    }
}


#endif //PROTO_CLIENT_HPP__
