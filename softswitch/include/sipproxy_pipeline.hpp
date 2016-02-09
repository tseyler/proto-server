//
// Created by tseyler on 2/9/16.
//

#ifndef SIPPROXY_PIPELINE_HPP_
#define SIPPROXY_PIPELINE_HPP_


#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

class sipproxy_pipeline : public proto_net_pipeline // pipeline for a server
{
public:

    void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);  // the response data
    void ps_pipe_in(proto_net_in_data& in_data) {}
    void ps_pipe_out(proto_net_out_data& out_data) {}
};


#endif //SIPPROXY_PIPELINE_HPP_
