
#include "c4soap.hpp"
#include "director.hpp"

using namespace c4soap;

std::string 
director::authenticate_password(int& seq, const params_array& /*params*/)
{
    std::stringstream ss;
    begin_c4soap_message(ss, "AuthenticatePassword", seq);
    param(ss, "password", "string", "root");
    end_c4soap_message(ss);
    
    return ss.str();
}

std::string 
director::get_version_info(int& seq, const params_array& /*params*/)
{
    std::stringstream ss;
    begin_c4soap_message(ss, "GetVersionInfo", seq);
    end_c4soap_message(ss);
    
    return ss.str(); 
}

std::string 
director::get_director_info(int& seq, const params_array& /*params*/)
{
    std::stringstream ss;
    begin_c4soap_message(ss, "GetDirectorInfo", seq);
    end_c4soap_message(ss);
    
    return ss.str(); 
}

std::string 
director::get_devices_by_interface(int& seq, const params_array& params)
{
	std::stringstream ss;
	begin_c4soap_message(ss, "GetDevicesByInterface", seq);
	param(ss, "GUID", "string", params[0]);
	end_c4soap_message(ss);
   
    return ss.str();
}

std::string 
director::get_devices_by_c4i(int& seq, const params_array& params)
{
	std::stringstream ss;
	begin_c4soap_message(ss, "GetDevicesByC4i", seq);
	param(ss, "c4i_name", "string", params[0]);
	end_c4soap_message(ss);
   
    return ss.str();
}

std::string 
director::send_to_device(int& seq, const params_array& params)
{
	std::stringstream ss;

	if (params.size() > 1)
	{
		std::string id = params[0];
		std::string cmd = params[1];

		begin_c4soap_message(ss, "SendToDevice", seq);	
		param(ss, "iddevice", "ulong", id);
		cmd = "<command>" + cmd + "</command>";
		if (params.size() > 2)
		{
			std::string param = "";
			for (size_t i = 2; i < params.size(); i++)
			{
				size_t j = i + 1;
				if (j < params.size())
				{
					param += get_param_value(params[i], params[j]);
				}
				else
					break;
			}
			std::string params = "<params>" + param + "</params>";
			cmd += params;
		}
		std::string root = get_param("root", "xml", cmd);
		param(ss, "data", "xml", root);
		end_c4soap_message(ss);
	}

    return ss.str();
}