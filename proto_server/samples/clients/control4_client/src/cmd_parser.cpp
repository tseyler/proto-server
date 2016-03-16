
#include <sstream>
#include "cmd_parser.hpp"

using namespace proto_net::protocol;

cmd_parser::cmd_parser(char** args, int cnt) : host_("127.0.0.1"),
												cmd_("GetVersionInfo"),
												parsed_(false)
{
	int idx(0);

	if (SAFE_INDEX( idx, cnt ))
		host_ = args[idx++];

	if (SAFE_INDEX( idx, cnt ))
		cmd_ = args[idx++];

	while (SAFE_INDEX( idx, cnt ))
		params_.push_back(std::string(args[idx++]));

	initialize_command_map();
}

cmd_parser::cmd_parser(const std::string& raw_string) : host_("127.0.0.1"),
														cmd_("GetVersionInfo"),
														parsed_(false)
{
	parse(raw_string);

	initialize_command_map();
}

void 
cmd_parser::initialize_command_map(void)
{
	// insert into the map
	director_command_map["AuthenticatePassword"] = c4soap::authenticate_password;
	director_command_map["GetVersionInfo"] = c4soap::get_version_info;
	director_command_map["GetDevicesByInterface"] = c4soap::get_devices_by_interface;
	director_command_map["GetDevicesByC4i"] = c4soap::get_devices_by_c4i;
	director_command_map["SendToDevice"] = c4soap::send_to_device;
	director_command_map["GetDirectorInfo"] = c4soap::get_director_info;
}

std::string 
cmd_parser::to_authenticate(int& seq)
{
	return director_command_map["AuthenticatePassword"](seq, params_);
}

std::string 
cmd_parser::to_c4soap(int& seq)
{
	std::string soap("");
	parsed_ = true;

	// are we a director command?
	std::map<std::string,
			proto_net::protocol::c4soap::director_c4soap_function>::iterator command_it = director_command_map.find(cmd_);
	if (command_it != director_command_map.end())
		soap = (*command_it).second(seq, params_);
	else
		parsed_ = false;

	return soap;
}


bool 
cmd_parser::parse(const std::string& raw_string)
{
	bool is_parsed(false);

    std::list<std::string> tokens;
    std::istringstream iss(raw_string);
    std::string token;    
    while (std::getline(iss, token, ' ')) 
        tokens.push_back(token);
    
	if (tokens.size())
	{
		std::string cmd = tokens.front();
		tokens.pop_front();

		c4soap::params_array params;
		while (tokens.size())
		{
			params.push_back(tokens.front());
			tokens.pop_front();
		}

		set_command(cmd, params);
		is_parsed = !IS_EXIT( cmd );
	}

	return is_parsed;
}

void 
cmd_parser::set_command(std::string& cmd, c4soap::params_array& params)
{
	cmd_ = cmd;
	params_ = params; // a copy
}