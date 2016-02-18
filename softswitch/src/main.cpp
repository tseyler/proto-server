// main.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <core/server/proto_tcp_text_server.hpp>
#include <core/client/proto_tcp_text_client.hpp>
#include "sipproxy_pipeline.hpp"
#include "director_pipeline.hpp"

//#include <vector>
//#include <boost/thread.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>



using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::server;
using namespace proto_net::client;

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
    // step 1 - create the server TCP/5095
    proto_tcp_text_server sp_server(5095);   // port 5095
    // create a pipeline for the server
    sipproxy_pipeline sp_pipeline;
    // start accepting connections
    sp_server.ps_start_accept(sp_pipeline, 4096); // buffer size = 4096
    // start the service
    sp_server.ps_start();

    // step 2 - create the client TCP/5020
    // create a pipeline for the client
    director_pipeline dir_pipeline;
    // create the client
    proto_tcp_text_client dir_client("192.168.1.12", 5020, dir_pipeline);

    // prepare the downstream and upstream pipeline
    sp_pipeline.ps_proto_io(&dir_client);

    // authenticate c4soap message for director to allow a connection
    std::string auth = "<c4soap name=\"AuthenticatePassword\" seq=\"1\"><param name=\"password\" type=\"string\">root</param></c4soap>";
    proto_net_in_data cmd_data(auth);
    // connect to the downstream server (director)
    dir_client.ps_async_connect(cmd_data);
    // start the client service
    dir_client.ps_start();
    boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
//    //std::string cmd = "<c4soap name=\"GetVersionInfo\" seq=\"2\"></c4soap>";
    std::string cmd = "<c4soap name=\"SendToDevice\" seq=\"5\"><param name=\"iddevice\" type=\"number\">8</param><param name=\"data\" type=\"string\"><devicecommand><command>getRoute</command><params><param><name>index</name><value type=\"INTEGER\"><static>0</static></value></param></params></devicecommand></param></c4soap>";
    proto_net_in_data another_cmd_data(cmd);
    dir_client.ps_async_write(another_cmd_data);
    dir_client.ps_async_write(another_cmd_data);
    dir_client.ps_async_write(another_cmd_data);
    dir_client.ps_async_write(another_cmd_data);
    //dir_client.ps_async_write(another_cmd_data);
    //dir_client.ps_async_write(another_cmd_data);

    void* dummy(NULL);
    boost::thread console_thd(console_func, dummy);

    console_thd.join();

    dir_client.ps_stop();
    sp_server.ps_stop();

    std::cout << "Done." << std::endl;
    
    return 0;
}

