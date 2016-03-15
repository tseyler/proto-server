

#include <core/server/proto_tcp_text_server.hpp>
#include "proto_echo_server_pipeline.hpp"

using namespace proto_net::server;

int
main(int argc, char *argv[])
{
    proto_tcp_text_server server(9669);
    proto_echo_server_pipeline echo_pipeline;
    server.ps_start_accept(echo_pipeline, 4096);
    server.ps_run();

    return 0;
}