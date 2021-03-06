

#include <iostream>
#include "proto_echo_client_pipeline.hpp"

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::client;

int
main(int argc, char *argv[])
{
    proto_echo_client_pipeline pipeline;
    proto_tcp_text_client client("127.0.0.1", 9669, pipeline);
    pipeline.ps_proto_service(&client);

    proto_net_in_data echo_data("Hello World!");
    client.ps_async_connect(echo_data);
    if (client.ps_is_connected())
        client.ps_run();

    return 0;
}