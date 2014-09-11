

#include "cmd_parser.hpp"

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

	// insert into the map
	director_command_map["AuthenticatePassword"] = director::authenticate_password;
	director_command_map["GetVersionInfo"] = director::get_version_info;
	director_command_map["GetDevicesByInterface"] = director::get_devices_by_interface;
	director_command_map["GetDevicesByC4i"] = director::get_devices_by_c4i;
	director_command_map["SendToDevice"] = director::send_to_device;
	director_command_map["GetDirectorInfo"] = director::get_director_info;

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
	std::map<std::string, director::director_c4soap_function>::iterator command_it = director_command_map.find(cmd_);
	if (command_it != director_command_map.end())
		soap = (*command_it).second(seq, params_);
	else
		parsed_ = false;

	return soap;
}

void 
cmd_parser::set_command(std::string& cmd, director::params_array& params)
{
	
}

}