//
// Created by tseyler on 2/10/16.
//

#include <iostream>
#include "director_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>

using namespace proto_net::data;
using namespace proto_net::server;

director_pipeline::director_pipeline(proto_tcp_session* us_tcp_session /*= NULL*/) : proto_tcp_client_pipeline(us_tcp_session)
{
}

void
director_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
    //proto_net_client_pipeline::ps_pipeline(req_data, res_data);
}

void
director_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    std::cout << "Director Pipeline: Data in = " << in_data << std::endl;
}

void
director_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    std::cout << "Director Pipeline: Data out = " << out_data << std::endl;
}

