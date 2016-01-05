#include <iostream>

#include <core/server/proto_server.hpp>
#include <core/server/proto_tcp_server.hpp>
#include "proto_echo_io.hpp"


using namespace std;
using namespace proto_net;
using namespace proto_net::server;

int
main(int argc, char *argv[])
{
    proto_net_service ps_service;
    proto_tcp_server server(ps_service, 9669);
    proto_echo_io echo_io;
    server.ps_start_accept(echo_io, 4096);
    server.ps_run();

    return 0;
}