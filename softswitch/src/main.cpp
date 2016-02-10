// main.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <core/server/proto_tcp_server.hpp>
#include <core/client/proto_tcp_client.hpp>
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
    /*
    proto_tcp_server sp_server(5095);   // port 5095
    sipproxy_pipeline sp_pipeline;
    sp_server.ps_start_accept(sp_pipeline, 4096); // buffer size = 4096
*/
    //std::string cmd = "<c4soap name=\"EnableEvents\" seq=\"1\"><param name=\"enable\" type=\"bool\">0</param></c4soap>";
    //  "password", "string", "root");
    std::string auth = "<c4soap name=\"AuthenticatePassword\" seq=\"1\" async=\"True\"><param name=\"password\" type=\"string\">root</param></c4soap>";
   // std::string cmd = "<c4soap name=\"GetVersionInfo\" seq=\"1\" async=\"True\"></c4soap>";
    director_pipeline dir_pipeline;
    proto_tcp_client dir_client("192.168.1.18", 5020, dir_pipeline);
    dir_pipeline.ps_proto_service(&dir_client);

    proto_net_in_data cmd_data(auth);
    dir_client.ps_async_connect(cmd_data);
    dir_client.ps_run();
/*
    try
    {
        dir_client.ps_connect();
    }
    catch (proto_net_error_code error)
    {
        std::cerr << error.message() << std::endl;
        return 1;
    }

    dir_client.ps_write_msg(auth);
    std::string res = dir_client.ps_read_msg();
*/
    //sp_server.ps_run();
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
   // std::cout << res << std::endl;
    std::cout << "Done";
    
    return 0;
}

