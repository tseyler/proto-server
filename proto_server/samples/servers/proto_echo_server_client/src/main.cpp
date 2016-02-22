

#include <core/server/proto_tcp_text_server.hpp>
#include "proto_echo_server_pipeline.hpp"
#include "proto_echo_client_pipeline.hpp"

using namespace proto_net::server;
using namespace proto_net::client;

int
main(int argc, char *argv[])
{
    proto_tcp_text_server server(9669);
    proto_echo_server_pipeline echo_server_pipeline;
    server.ps_start_accept(echo_server_pipeline, 4096);
    server.ps_start(); // start the server

    proto_echo_client_pipeline echo_client_pipeline;
    proto_tcp_text_client client("127.0.0.1", 9669, echo_client_pipeline);

    proto_net_in_data echo_data("Hello World!");
    client.ps_async_connect(echo_data);
    client.ps_start();

    proto_net_in_data another_data("Another Hello World!");
    client.ps_async_write(another_data);
    client.ps_async_write(another_data);
    client.ps_async_write(another_data);
    client.ps_async_write(another_data);
    client.ps_async_write(another_data);

    client.ps_stop();
    server.ps_stop();

    return 0;
}