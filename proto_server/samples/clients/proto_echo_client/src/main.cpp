

#include <iostream>
#include "proto_echo_pipeline.hpp"

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::client;

int
main(int argc, char *argv[])
{
    proto_echo_pipeline pipeline;
    proto_tcp_client client("127.0.0.1", 9669);

    try
    {
       client.ps_connect();
    }
    catch (proto_net_error_code& ec)
    {
        std::cout << "Could not connect; Error = " << ec.message() << std::endl;
        return 1;
    }
/*
    proto_echo_pipeline pipeline(client);
    proto_net_in_data in_data("Hello World!");
    proto_net_out_data out_data;
    pipeline.ps_pipeline(in_data, out_data);
*/
   // client.ps_write_msg("Hello World!");
    //std::string response = client.ps_read_msg();
    //std::cout << response << std::endl;

    return 0;
}