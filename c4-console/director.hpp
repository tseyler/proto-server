#ifndef DIRECTOR_HPP__
#define DIRECTOR_HPP__

#include <string.h>
#include <sstream>
#include <vector>

#include "c4soap.hpp"

namespace director
{
	typedef std::vector<std::string> params_array;

	typedef std::string(*director_c4soap_function)(int&, const params_array&);

	// always authenicate before issuing commands
	std::string authenticate_password(int& seq, const params_array& params);

	// gets the version of the director that you are connected to
	std::string get_version_info(int& seq, const params_array& params);

	// use a guid to get a device.  Useful for agents
	std::string get_devices_by_interface(int& seq, const params_array& params);

	// use a c4i name to get a device(s)
	std::string get_devices_by_c4i(int& seq, const params_array& params);

	// use this to send a commmand to a device
	std::string send_to_device(int& seq, const params_array& params);

	// gets info on director
	std::string get_director_info(int& seq, const params_array& params);
}

#endif