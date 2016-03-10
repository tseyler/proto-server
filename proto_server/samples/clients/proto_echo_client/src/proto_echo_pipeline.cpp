//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_pipeline.hpp"
#include <core/data/proto_net_string_data.hpp>


void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    // convert
}

void
proto_echo_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    if (in_data.data_size())
    {
        proto_net_string_data txt_data(in_data);
        std::cout << "Echo Client Pipeline: Send = " << txt_data.to_string() << std::endl;
    }

}

void
proto_echo_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    if (out_data.data_size())
    {
        proto_net_string_data txt_data(out_data);
        std::cout << "Echo Client Pipeline: Received = " << txt_data.to_string() << std::endl;
    }

    if (ps_proto_service())
        ps_proto_service()->ps_stop();
}
