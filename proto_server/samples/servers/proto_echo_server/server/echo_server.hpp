//
// Created by Terry Seyler on 9/1/15.
//

#ifndef ECHO_SERVER_HPP__
#define ECHO_SERVER_HPP__

#include <core/server/proto_tcp_server.hpp>

using namespace proto_net;
using namespace proto_net::server;

class echo_server : public proto_tcp_server
{
public:

    echo_server(unsigned short port_num = 9669);

    // copy constructor
    echo_server(const echo_server& es);

    virtual ~echo_server();

    echo_server& clone(const echo_server& ps);

    echo_server& operator =(const echo_server& ps);

    // pure virtuals
    virtual void ps_initialize(void);
    virtual void ps_run(void);
    virtual void ps_io(const proto_net_data& req_data, proto_net_data& res_data);

protected:

  //  virtual void ps_start_accept(void);

};

#endif

