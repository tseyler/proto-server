// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <ifaddrs.h>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include "sipclient_signaling.hpp"
#include <string>


using namespace sipclient;

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

boost::mutex reg_mutex;

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

void console_func(sipclient_signaling* uas)
{
	bool alive(true);
	boost::mutex::scoped_lock lock(reg_mutex);
	std::string console_input;
	uas->restart_useragent(0, false,  "sipclient");
	//boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
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

std::string get_local_address(void)
{
	std::string fnd_address("127.0.0.1");

	struct ifaddrs* if_struct_ptr(NULL);
	struct ifaddrs* ifa(NULL);
	void* tmp_addr(NULL);

	char addressBuffer[32];

	getifaddrs(&if_struct_ptr);

	for (ifa = if_struct_ptr; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (!ifa->ifa_addr)
			continue;
		memset(addressBuffer, 0, 32);
		if (ifa->ifa_addr->sa_family == AF_INET)
		{ // check it is IP4
			// is a valid IP4 Address
			tmp_addr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
			inet_ntop(AF_INET, tmp_addr, addressBuffer, 32);
			std::string ab(addressBuffer);
			std::string ba = ab;
			fnd_address = ba;
			std::cout << ba << std::endl;
		}
		else if (ifa->ifa_addr->sa_family == AF_INET6)
		{ // check it is IP6
			// is a valid IP6 Address
			tmp_addr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
			inet_ntop(AF_INET6, tmp_addr, addressBuffer, 32);
			//local_address = addressBuffer;
		}
	}

	free(if_struct_ptr);

	return fnd_address;
}

class console_notifier : public sipclient_notifier
{
public:

	void sipclient_notify(layer_sipclient layer, unsigned short layer_event, const std::string& notify_msg)
	{
		std::cout << "Console: Event Layer = " << layer <<  "; Event = " << layer_event << "; Event Message = " << notify_msg << std::endl;
	}
};

int 
main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: sipclient <name> <username> <registrar>" << std::endl;
		return 1;
	}


	console_notifier cn;
	sipclient_logger_ptr logger_ptr(new sipclient_logger(std::cout));
	sipclient_notification_ptr notification_ptr(new sipclient_notification(logger_ptr, &cn));

	//std::string profile_aor = sipclient_signaling::set_profile_aor("sipclient_app", "2109", "192.168.1.10");
	std::string name = argv[1];
	std::string username = argv[2];
	std::string registrar = argv[3];
	std::string profile_aor = sipclient_signaling::set_profile_aor(name, username, registrar);
	std::string local_address = get_local_address();
    sipclient_signaling uas(local_address, profile_aor, logger_ptr, notification_ptr);

    boost::thread console_thd(console_func, &uas);

    console_thd.join();
	// stop the UA loop
    uas.stop_useragent();

    std::cout << "Done";

    return 0;
}

