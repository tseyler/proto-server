//
//  c4soap_director.hpp - c4soap director messages
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
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

            typedef std::string(*director_c4soap_function)(unsigned long&, const params_array&);

            bool is_async_c4soap(const std::string& soap);

            // always authenicate before issuing commands
            std::string authenticate_password(unsigned long& seq, const params_array& params);

            // gets the version of the director that you are connected to
            std::string get_version_info(unsigned long& seq, const params_array& params);

            // use a guid to get a device.  Useful for agents
            std::string get_devices_by_interface(unsigned long& seq, const params_array& params);

            // use a c4i name to get a device(s)
            std::string get_devices_by_c4i(unsigned long& seq, const params_array& params);

            // use this to send a commmand to a device
            std::string send_to_device(unsigned long& seq, const params_array& params);

            std::string send_async_to_device(unsigned long& seq, const params_array& params);

            // gets info on director
            std::string get_director_info(unsigned long& seq, const params_array& params);

            // register an event listener
            std::string register_event_listener(unsigned long& seq, const params_array& params);

            // unregister an event listener
            std::string unregister_event_listener(unsigned long& seq, const params_array& params);
        }
    }
}


#endif //C4SOAP_DIRECTOR_HPP_
