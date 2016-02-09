//
// Created by tseyler on 2/9/16.
//

#include <iostream>
#include "sipproxy_pipeline.hpp"
#include <core/data/proto_net_pipe.hpp>


void
sipproxy_pipeline::ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data)
{
   // proto_net_pipe pipe(req_data);
    proto_net_data data_in = req_data;
    data_in.data_type(data_text);
    std::cout << "SipProxy Pipeline: Data in = " << data_in << std::endl;
   // res_data = pipe.ps_pipe_data_out();
    //proto_net_data data_out = res_data;
   // data_out.data_type(data_text);
   // std::cout << "SipProxy Pipeline: Data out = " << data_out << std::endl;
}

