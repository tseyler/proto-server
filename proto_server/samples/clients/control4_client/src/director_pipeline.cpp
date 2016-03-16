//
// Created by tseyler on 2/10/16.
//

#include <iostream>
#include "director_pipeline.hpp"
#include <core/data/proto_net_string_data.hpp>

using namespace proto_net::data;


director_pipeline::director_pipeline(const std::string& da) : director_address_(da)
{}

void
director_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
}

void
director_pipeline::ps_pipe_in(proto_net_in_data& in_data)
{
    //boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    proto_net_string_data in_txt_data(in_data);
    std::cout << "Director@" << director_address_ << " [c4soap request] " << in_txt_data.to_string() << std::endl;
}

void
director_pipeline::ps_pipe_out(proto_net_out_data& out_data)
{
   // boost::unique_lock<boost::mutex> scoped_lock(mutex_);
    proto_net_string_data out_txt_data(out_data);
    std::cout << "Director@" << director_address_ << " [c4soap response] " << out_txt_data.to_string() << std::endl;
}

