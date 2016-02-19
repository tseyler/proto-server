// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include <core/client/proto_tcp_text_client.hpp>
#include "director_pipeline.hpp"

//#include <vector>
//#include <boost/thread.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>



using namespace proto_net::data;
using namespace proto_net;
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

int seq = 1;

std::string
new_sequenced_cmd(void)
{
    std::stringstream ss;
    ss <<  "<c4soap name=\"SendToDevice\"";
    ss << " seq=\"" << ++seq << "\">";
    ss << "<param name=\"iddevice\" type=\"number\">8</param><param name=\"data\" type=\"string\"><devicecommand><command>getRoute</command><params><param><name>index</name><value type=\"INTEGER\"><static>0</static></value></param></params></devicecommand></param></c4soap>";

    return ss.str();
}


int 
main(int argc, char* argv[])
{
    // create a pipeline for the client
    director_pipeline dir_pipeline;
    // create the client
    proto_tcp_text_client dir_client("192.168.1.12", 5020, dir_pipeline);

    // authenticate c4soap message for director to allow a connection
    std::string auth = "<c4soap name=\"AuthenticatePassword\" seq=\"1\"><param name=\"password\" type=\"string\">root</param></c4soap>";
    proto_net_in_data cmd_data(auth);
    // connect to the downstream server (director)
    dir_client.ps_async_connect(cmd_data);
    // start the client service
    dir_client.ps_start();

//    //std::string cmd = "<c4soap name=\"GetVersionInfo\" seq=\"2\"></c4soap>";

    //std::string cmd = "<c4soap name=\"SendToDevice\" seq=\"2\"><param name=\"iddevice\" type=\"number\">8</param><param name=\"data\" type=\"string\"><devicecommand><command>getRoute</command><params><param><name>index</name><value type=\"INTEGER\"><static>0</static></value></param></params></devicecommand></param></c4soap>";
    std::string cmd = new_sequenced_cmd();
    proto_net_in_data another_cmd_data(cmd);
    dir_client.ps_async_write(another_cmd_data);

    cmd = new_sequenced_cmd();
    another_cmd_data = proto_net_in_data(cmd);
    dir_client.ps_async_write(another_cmd_data);

    cmd = new_sequenced_cmd();
    another_cmd_data = proto_net_in_data(cmd);
    dir_client.ps_async_write(another_cmd_data);

    cmd = new_sequenced_cmd();
    another_cmd_data = proto_net_in_data(cmd);
    dir_client.ps_async_write(another_cmd_data);

    cmd = new_sequenced_cmd();
    another_cmd_data = proto_net_in_data(cmd);
    dir_client.ps_async_write(another_cmd_data);

    void* dummy(NULL);
    boost::thread console_thd(console_func, dummy);

    console_thd.join();

    dir_client.ps_stop();

    std::cout << "Done." << std::endl;
    
    return 0;
}

