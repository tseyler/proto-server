//
// Created by tseyler on 1/26/16.
//

#ifndef PROTO_NET_PIPE_HPP_
#define PROTO_NET_PIPE_HPP_

#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_pipe
        {
        public:

            proto_net_pipe(const proto_net_in_data& data_in);
            virtual ~proto_net_pipe();

            proto_net_in_out_data ps_pipe_out(void) const;

        protected:

            proto_net_in_out_data data_in_;

        };
    }
}

#endif //PROTO_NET_PIPE_HPP_
