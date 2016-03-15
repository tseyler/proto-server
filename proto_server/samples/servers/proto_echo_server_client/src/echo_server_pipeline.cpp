//
// Created by tseyler on 2/13/16.
//

#include <iostream>
#include "echo_server_pipeline.hpp"
#include <core/data/proto_net_string_data.hpp>

void
echo_server_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    if (req_data.data_size())
    {
        proto_net_string_data req_txt_data(req_data);
        std::cout << "Echo Server Pipeline: Received = " << req_txt_data.to_string() << std::endl;
    }

    res_data = req_data;

    if (res_data.data_size())
    {
        proto_net_string_data res_txt_data(req_data);
        std::cout << "Echo Server Pipeline: Send = " << res_txt_data.to_string() << std::endl;
    }
}
