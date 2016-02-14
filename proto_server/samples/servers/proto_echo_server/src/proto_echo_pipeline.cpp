//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>

void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    proto_net_pipe pipe(req_data);
    proto_net_data data_in = req_data;
    //data_in.data_type(data_text);
    std::cout << "Echo Server Pipeline: Send = " << data_in << std::endl;
    res_data = pipe.ps_pipe_data_out();
    proto_net_data data_out = res_data;
   // data_out.data_type(data_text);
    std::cout << "Echo Server Pipeline: Received = " << data_out << std::endl;
}
