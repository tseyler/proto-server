//
// Created by tseyler on 1/4/16.
//

#ifndef PROTO_ECHO_SERVER_PIPELINE_HPP_
#define PROTO_ECHO_SERVER_PIPELINE_HPP_

#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

class proto_echo_server_pipeline : public proto_net_pipeline // pipeline for a server
{
public:

    void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);  // the response data
    bool ps_pipe_in(proto_net_in_data& in_data) { return true; }
    void ps_pipe_out(proto_net_out_data& out_data) {}
};


#endif //PROTO_ECHO_SERVER_PIPELINE_HPP_
