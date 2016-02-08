//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>


void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    // convert
}

void
proto_echo_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    if (in_data.data_size())
        std::cout << "Echo Client Pipeline: Data in = " << in_data << std::endl;
}

void
proto_echo_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    if (out_data.data_size())
    {
        out_data.data_type(data_text);
        std::cout << "Echo Client Pipeline: Data out = " << out_data << std::endl;
    }

    if (ps_proto_service())
        ps_proto_service()->ps_stop();
}
