//
// Created by tseyler on 1/4/16.
//

#include "proto_echo_io.hpp"

void
proto_echo_io::ps_io(const proto_net_data& req_data, proto_net_data& res_data)
{
    res_data = req_data; // here is how we echo
}
