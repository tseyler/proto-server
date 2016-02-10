//
// Created by tseyler on 2/10/16.
//

#ifndef DIRECTOR_PIPELINE_HPP_
#define DIRECTOR_PIPELINE_HPP_

#include <core/server/proto_session.hpp>

using namespace proto_net::data;
using namespace proto_net::server;

class director_pipeline : public proto_net_client_pipeline // pipeline for a client
{
public:

    director_pipeline(proto_session* us_session = NULL);
    virtual ~director_pipeline()
    {}

    void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data);  // the response data
    void ps_pipe_in(proto_net_in_data& in_data);
    void ps_pipe_out(proto_net_out_data& out_data);
};

#endif //DIRECTOR_PIPELINE_HPP_
