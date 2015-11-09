//
// Created by Terry Seyler on 10/25/15.
//

#ifndef PROTO_SERVER_PROTO_NET_IO_HPP_
#define PROTO_SERVER_PROTO_NET_IO_HPP_

#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_io
        {
        public:

            virtual void ps_io(const proto_net_data& req_data, proto_net_data& res_data) = 0;  // the response data
        };
    }
}
#endif //PROTO_SERVER_PROTO_NET_IO_HPP_
