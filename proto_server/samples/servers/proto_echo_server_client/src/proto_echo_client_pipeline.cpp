//
// Created by tseyler on 2/13/16.
//

#include <iostream>
#include "proto_echo_client_pipeline.hpp"


void
proto_echo_client_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    // convert
}

void
proto_echo_client_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    if (in_data.data_size())
        std::cout << "Echo Client Pipeline: Send = " << in_data << std::endl;
}

void
proto_echo_client_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    if (out_data.data_size())
    {
        out_data.data_type(data_text);
        std::cout << "Echo Client Pipeline: Received = " << out_data << std::endl;
    }
}
