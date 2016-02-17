// main.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <core/server/proto_tcp_text_server.hpp>
#include <core/client/proto_tcp_text_client.hpp>
#include "sipproxy_pipeline.hpp"
#include "director_pipeline.hpp"

/*
#include <vector>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
*/


using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::server;
using namespace proto_net::client;


//typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

/*
void parse_console_line(sipclient_signaling* uas, const std::string& console_input)
{
	boost::char_separator<char> sep(" \t\r\n");
	tokenizer tokens(console_input, sep);

	tokenizer::iterator tok_iter = tokens.begin();
	if (tok_iter == tokens.end())
		return;

	std::string cmd = *tok_iter++;
	std::vector<std::string> params;

	while (tok_iter != tokens.end())
		params.push_back(*tok_iter++);

	std::string call_id = uas->get_call_id();
	if (boost::iequals(cmd, "answer"))
		uas->execute_offer_useragent(call_id);
	if (boost::iequals(cmd, "reject"))
		uas->execute_offer_useragent(call_id, false, 486); // busy here
	if (boost::iequals(cmd, "bye"))
		uas->execute_bye_useragent(call_id);
	if (boost::iequals(cmd, "invite"))
	{
		std::string remote_uri = params[0];
		uas->execute_invite_useragent(remote_uri);
	}
//	if (boost::iequals(cmd, "transport"))
//	{
//		std::string transport_type = params[0];
//		bool is_tcp = bool(boost::iequals(transport_type, "tcp"));
//		std::string profile_aor = sipclient_signaling::set_profile_aor("UA_Console_App", "UA_Console_App", "10.0.0.14");
//		uas->restart_useragent(0, is_tcp, profile_aor, "t0talc0ntr0l4!");
//	}
}
*/
/*
void console_func(sipclient_signaling* uas)
{
	bool alive(true);
	boost::mutex::scoped_lock lock(reg_mutex);
	std::string console_input;
	uas->restart_useragent(0, false,  "sipclient");
	while (!uas->is_registered())
		uas->registration_condition().wait(lock);

	while (alive)
	{
		std::cout << "sipclient >> ";
		std::getline(std::cin, console_input);
		//std::cout << console_input << std::endl;
		if (boost::iequals(console_input, "exit"))
			alive = false;

		parse_console_line(uas, console_input);
	}

	std::cout << "Exiting..." << std::endl;
}
*/


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
    //dir_pipeline.ps_proto_io(&dir_client);
    sp_pipeline.ps_proto_io(&dir_client);

    // authenticate c4soap message for director to allow a connection
    std::string auth = "<c4soap name=\"AuthenticatePassword\" seq=\"1\"><param name=\"password\" type=\"string\">root</param></c4soap>";
    proto_net_in_data cmd_data(auth);
    // connect to the downstream server (director)
    dir_client.ps_async_connect(cmd_data);
    // start the client service
    dir_client.ps_start();

    //boost::this_thread::sleep(boost::posix_time::milliseconds(500));

    //std::string cmd = "<c4soap name=\"GetVersionInfo\" seq=\"2\"></c4soap>";
    //proto_net_in_data another_cmd_data(cmd);
   // dir_client.ps_async_write(another_cmd_data);

    boost::this_thread::sleep(boost::posix_time::milliseconds(60000));

    dir_client.ps_stop();
    sp_server.ps_stop();

    /*
	if (argc != 4)
	{
		std::cout << "Usage: sipclient <name> <username> <registrar>" << std::endl;
		return 1;
	}


    boost::thread console_thd(console_func, &uas);

    console_thd.join();
	// stop the UA loop
    */
   // std::cout << res << std::endl;
    std::cout << "Done";
    
    return 0;
}

