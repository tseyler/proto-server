

#include <iostream>
#include "proto_echo_pipeline.hpp"

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::client;

int
main(int argc, char *argv[])
{
    proto_echo_pipeline pipeline;
    proto_tcp_client client("127.0.0.1", 9669, pipeline);

    proto_net_in_data echo_data("Hello World!");

    client.ps_async_connect(echo_data);
    client.ps_run();

    return 0;
}