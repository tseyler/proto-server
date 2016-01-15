// main.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <iostream>
#include <vector>
// #include <boost/thread.hpp>
// #include <boost/date_time.hpp>
// #include <boost/algorithm/string.hpp>
// #include <boost/tokenizer.hpp>
// #include <boost/foreach.hpp>

#include "useragent_signaling.hpp"

using namespace sipclient_console_app;

// typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
/*
void parse_console_line(useragent_signaling* uas, const std::string& console_input)
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
	if (boost::iequals(cmd, "bye"))
		uas->execute_bye_useragent(call_id);
	if (boost::iequals(cmd, "invite"))
	{
		std::string remote_uri = params[0];
		uas->execute_invite_useragent(remote_uri);
	}
	if (boost::iequals(cmd, "transport"))
	{
		std::string transport_type = params[0];
		bool is_tcp = bool(boost::iequals(transport_type, "tcp"));
		std::string profile_aor = useragent_signaling::set_profile_aor("UA_Console_App", "UA_Console_App", "10.0.0.14");
		uas->restart_useragent(0, is_tcp, profile_aor, "t0talc0ntr0l4!");
	}
}

void console_func(useragent_signaling* uas)
{
	bool alive(true);
	std::string console_input;
	while (alive)
	{
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
	useragent_signaling uas("192.168.1.6");

	//restart_useragent(int port, bool bDisableUDP, const char* passwd)
	// init
	//uas.init();
	// set the profile
	//uas.set_profile_aor("UA_Console_App", "UA_Console_App", "10.0.0.14");
	// start the UA loop
	//uas.start_useragent();
//	std::string profile_aor = useragent_signaling::set_profile_aor("UA_Console_App", "UA_Console_App", "10.0.0.14");

//	uas.restart_useragent(0, false, profile_aor, "t0talc0ntr0l4!");

//	boost::thread console_thd(console_func, &uas);

//	console_thd.join();
	// stop the UA loop
//	uas.stop_useragent();

    std::cout << "Done";

    return 0;
}

