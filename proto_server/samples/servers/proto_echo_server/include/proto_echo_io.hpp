//
// Created by tseyler on 1/4/16.
//

#ifndef PROTO_ECHO_SERVER_PROTO_ECHO_IO_HPP_
#define PROTO_ECHO_SERVER_PROTO_ECHO_IO_HPP_

#include <core/data/proto_net_io.hpp>

using namespace proto_net::data;

class proto_echo_io : public proto_net_io
{
public:

    virtual void ps_io(const proto_net_data& req_data, proto_net_data& res_data);  // the response data
};


#endif //PROTO_ECHO_SERVER_PROTO_ECHO_IO_HPP_
