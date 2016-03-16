//
// Created by tseyler on 3/16/16.
//

#ifndef C4SOAP_DIRECTOR_HPP_
#define C4SOAP_DIRECTOR_HPP_

#include <vector>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
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
    }
}


#endif //C4SOAP_DIRECTOR_HPP_
