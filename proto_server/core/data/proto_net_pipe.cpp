//
// Created by tseyler on 1/26/16.
//

#include <core/data/proto_net_pipe.hpp>


namespace proto_net
{
    namespace data
    {
        proto_net_pipe::proto_net_pipe(const proto_net_in_data& data_in) : data_in_(data_in)
        {
        }

        proto_net_pipe::~proto_net_pipe()
        {
        }

        proto_net_in_out_data proto_net_pipe::ps_pipe_out(void) const
        {
            return data_in_;
        }
    }
}

