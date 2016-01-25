//
// Created by tseyler on 1/4/16.
//

#include "proto_echo_pipeline.hpp"

void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    res_data = req_data; // here is how we echo
}
