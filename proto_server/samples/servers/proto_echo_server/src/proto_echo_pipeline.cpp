//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>

void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    //res_data = req_data; // here is how we echo
    proto_net_pipe pipe(req_data);
    std::cout << "Echo Server Pipeline: Data in = " << req_data << std::endl;
    res_data = pipe.ps_pipe_out();
    std::cout << "Echo Server Pipeline: Data out = " << res_data << std::endl;
}
