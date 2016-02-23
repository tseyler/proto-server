//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_pipeline.hpp"


void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    std::cout << "Echo Server Pipeline: Send = " << req_data << std::endl;
    std::cout << "Echo Server Pipeline: Received = " << res_data << std::endl;
}
