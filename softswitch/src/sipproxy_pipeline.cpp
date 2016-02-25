//
// Created by tseyler on 2/9/16.
//

#include <iostream>
#include "sipproxy_pipeline.hpp"

using namespace proto_net::data;
using namespace proto_net::client;


void
sipproxy_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
}

void
sipproxy_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    print_pipe_in(in_data);
    proto_tcp_downstream_pipeline::ps_pipe_in(in_data);
}

void
sipproxy_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    print_pipe_out(out_data);
}

void
sipproxy_pipeline::print_pipe_in(proto_net_in_data& in_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    std::cout << "(1) SipProxy Pipeline: Received Data = " << in_data << std::endl;
    std::cout << "(2) =========> Forwarding downstream to client." << std::endl;
}

void
sipproxy_pipeline::print_pipe_out(proto_net_out_data& out_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    std::cout << "(6) SipProxy Pipeline: Sent Data = " << out_data << std::endl;
    std::cout << "[Round trip completed]" << std::endl << std::endl;
}

