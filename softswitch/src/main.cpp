// main.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <core/server/proto_tcp_server.hpp>
#include "sipproxy_pipeline.hpp"

/*
#include <vector>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
*/


using namespace proto_net::data;
using namespace proto_net;
using namespace proto_net::server;


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
    proto_tcp_server sp_server(5095);
    sipproxy_pipeline sp_pipeline;
    sp_server.ps_start_accept(sp_pipeline, 4096);
    sp_server.ps_run();
    /*
	if (argc != 4)
	{
		std::cout << "Usage: sipclient <name> <username> <registrar>" << std::endl;
		return 1;
	}



	//std::string profile_aor = sipclient_signaling::set_profile_aor("sipclient_app", "2109", "192.168.1.10");
	std::string name = argv[1];
	std::string username = argv[2];
	std::string registrar = argv[3];
	std::string profile_aor = sipclient_signaling::set_profile_aor(name, username, registrar);
	std::string local_address = get_local_address();
    sipclient_signaling uas(local_address, profile_aor, logger_ptr);

    boost::thread console_thd(console_func, &uas);

    console_thd.join();
	// stop the UA loop
    uas.stop_useragent();
    */
    std::cout << "Done";
    
    return 0;
}

