

#include <iostream>
#include <core/client/proto_tcp_client.hpp>

using namespace proto_net;
using namespace proto_net::client;

int
main(int argc, char *argv[])
{
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

    client.ps_write_msg("Hello World!");
    std::string response = client.ps_read_msg();
    std::cout << response << std::endl;

    return 0;
}