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
            bool
            c4soap_sendtodevice::is_response(const c4soap_message& msg, unsigned long seq)
            {
                return (boost::equal(msg.c4soap_name(), c4soap_cmd_sendtodevice) && seq == msg.c4soap_seq());
            }

            c4soap_sendtodevice::c4soap_sendtodevice(const c4soap_message& msg, const std::string& device_command) :
                    c4soap_message(msg),
                    device_command_(device_command)
            { }
        }
    }
}