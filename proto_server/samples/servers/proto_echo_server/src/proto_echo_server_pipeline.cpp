//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_server_pipeline.hpp"
#include <core/data/proto_net_string_data.hpp>


void
proto_echo_server_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    if (req_data.data_size())
    {
        proto_net_string_data req_txt_data(req_data);
        std::cout << "Echo Server Pipeline: Received = " << req_txt_data.to_string() << std::endl;
    }

    if (res_data.data_size())
    {
        proto_net_string_data res_txt_data(res_data);
        std::cout << "Echo Server Pipeline: Send = " << res_txt_data.to_string() << std::endl;
    }
}
