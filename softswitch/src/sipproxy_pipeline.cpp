//
// Created by tseyler on 2/9/16.
//

#include <iostream>
#include "sipproxy_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>

using namespace proto_net::data;
using namespace proto_net::client;


void
sipproxy_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
}

void
sipproxy_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    std::cout << "SipProxy Pipeline: Send Data  = " << in_data << std::endl;
    std::cout << " =========> Forwarding downstream to client." << std::endl;

    proto_tcp_downstream_pipeline::ps_pipe_in(in_data);
}

void
sipproxy_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    std::cout << "SipProxy Pipeline: Received Data  = " << out_data << std::endl;
    std::cout << "[Round trip complete]" << std::endl << std::endl;
}

