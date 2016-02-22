//
// Created by tseyler on 2/10/16.
//

#include <iostream>
#include "director_pipeline.hpp"

using namespace proto_net::data;


void
director_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
}

void
director_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{

    boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    std::cout << "Director Pipeline: Send Data = " << in_data << std::endl;
}

void
director_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    std::cout << "Director Pipeline: Received Data = " << out_data << std::endl;
    //ps_pipeline_unlock();
}

