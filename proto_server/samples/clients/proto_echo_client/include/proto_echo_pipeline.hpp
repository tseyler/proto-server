//
// Created by tseyler on 1/4/16.
//

#ifndef PROTO_ECHO_PIPELINE_HPP_
#define PROTO_ECHO_PIPELINE_HPP_

#include <core/data/proto_net_pipeline.hpp>
#include <core/client/proto_tcp_client.hpp>

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::client;

class proto_echo_pipeline : public proto_net_pipeline
{
public:

    virtual void ps_pipeline(const proto_net_data& req_data, proto_net_data& res_data);  // the response data
};


#endif //PROTO_ECHO_PIPELINE_HPP_
