//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <core/protocol/c4soap/c4soap_std_getuser.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            const std::string c4soap_std_getuser::c4soap_cmd_getuser = "getUser";

            bool
            c4soap_std_getuser::is_response(const c4soap_sendtodevice& msg, unsigned long seq)
            {
                bool is_getuser = c4soap_sendtodevice::is_response(msg, seq);
                if (is_getuser)
                        is_getuser = (boost::equal(msg.c4soap_device_commnd(), c4soap_cmd_getuser));

                return is_getuser;
            }

            c4soap_std_getuser::c4soap_std_getuser(const c4soap_message& msg) : c4soap_sendtodevice(msg, "getUser")
            {
                id_ = pt_.get<unsigned long>("c4soap.device.deviceId");
                user_ = pt_.get<std::string>("c4soap.device.user");
                domain_ = pt_.get<std::string>("c4soap.device.domain");
                password_ = pt_.get<std::string>("c4soap.device.password");
            }
        }
    }
}

