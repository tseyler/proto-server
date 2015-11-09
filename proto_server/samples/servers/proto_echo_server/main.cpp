#include <iostream>

//#include "server/echo_server.hpp"

#include <core/server/proto_tcp_server.hpp>



using namespace std;
using namespace proto_net::server;

int
main(int argc, char *argv[])
{

    proto_tcp_server server(9669);

    //server.ps_run();

    return 0;
}