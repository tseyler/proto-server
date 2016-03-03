//
// Created by tseyler on 2/13/16.
//

#ifndef PROTO_ECHO_CLIENT_PIPELINE_HPP_
#define PROTO_ECHO_CLIENT_PIPELINE_HPP_

#include <core/data/proto_net_pipeline.hpp>
#include <core/client/proto_tcp_text_client.hpp>

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::client;

class proto_echo_client_pipeline : public proto_net_pipeline
{
public:

    void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);  // the response data
    void ps_pipe_in(proto_net_in_data& in_data);
    void ps_pipe_out(proto_net_out_data& out_data);
    bool ps_pipe_error(proto_net_error_data& error_data) { return false; }
};


#endif //PROTO_ECHO_PIPELINE_HPP_
