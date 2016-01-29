//
// Created by tseyler on 1/4/16.
//

#include <iostream>
#include "proto_echo_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>


proto_echo_pipeline::proto_echo_pipeline(proto_tcp_client& client) : client_(client)
{

}

void
proto_echo_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    std::cout << "Echo Client Pipeline: Data in = " << req_data << std::endl;
    client_.ps_write_msg(req_data.to_string());
    std::string response = client_.ps_read_msg();
    res_data = proto_net_data(response);
    std::cout << "Echo Client Pipeline: Data out = " << res_data << std::endl;
}
