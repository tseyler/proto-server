// main.cpp : Defines the entry point for the console application.
//

#include <iostream>

//#include <core/server/proto_tcp_text_server.hpp>
//#include <core/client/proto_tcp_text_client.hpp>
#include <core/factory/proto_tcp_text_client_factory.hpp>
#include <core/factory/proto_tcp_text_server_factory.hpp>
#include "sipproxy_pipeline.hpp"
#include "director_pipeline.hpp"
#include <boost/algorithm/string.hpp>

using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::server;
using namespace proto_net::client;
using namespace proto_net::factory;

void console_func(void*)
{
	bool alive(true);
	std::string console_input;

	while (alive)
	{
		std::getline(std::cin, console_input);
		if (boost::iequals(console_input, "exit"))
			alive = false;
	}

	std::cout << "Exiting..." << std::endl;
}



int 
main(int argc, char* argv[])
{
    std::string director_address = argv[1];

    // step 1 - create the client TCP/5020
    // create a pipeline for the client
    director_pipeline dir_pipeline;
    // create the client
    std::string auth = "<c4soap name=\"AuthenticatePassword\" seq=\"1\"><param name=\"password\" type=\"string\">root</param></c4soap>";
    proto_net_in_data cmd_data(auth);
    proto_tcp_text_client_factory client_factory(director_address, cmd_data, 5020, dir_pipeline);
    proto_service_ptr director_client = client_factory();

    // step 2 - create the server TCP/5095
    // create a pipeline for the server
    sipproxy_pipeline sp_pipeline;
    sp_pipeline.ps_proto_io(proto_tcp_client::proto_async_io_cast(director_client));

    proto_tcp_text_server_factory server_factory(sp_pipeline, 5095);
    proto_service_ptr sipproxy_server = server_factory();

    void* dummy(NULL);
    boost::thread console_thd(console_func, dummy);

    console_thd.join();

    sipproxy_server->ps_stop();
    director_client->ps_stop();

    std::cout << "Done." << std::endl;

    return 0;
}

