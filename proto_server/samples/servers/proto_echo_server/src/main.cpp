

#include <iostream>
#include <core/server/proto_tcp_server.hpp>
#include "proto_echo_io.hpp"

using namespace proto_net::server;

int
main(int argc, char *argv[])
{
    proto_tcp_server server(9669);
    proto_echo_io echo_io;
    server.ps_start_accept(echo_io, 4096);
    server.ps_run();

    return 0;
}