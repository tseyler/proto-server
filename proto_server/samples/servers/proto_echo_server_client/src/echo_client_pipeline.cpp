//
// Created by tseyler on 2/13/16.
//

#include <iostream>
#include <core/data/proto_net_string_data.hpp>
#include "echo_client_pipeline.hpp"


void
echo_client_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    // convert
}

void
echo_client_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    if (in_data.data_size())
    {
        proto_net_string_data txt_data(in_data);
        std::cout << "Echo Client Pipeline: Send = " << txt_data.to_string() << std::endl;
    }

}

void
echo_client_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    if (out_data.data_size())
    {
        proto_net_string_data txt_data(out_data);
        std::cout << "Echo Client Pipeline: Received = " << txt_data.to_string() << std::endl;
    }
}
