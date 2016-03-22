//
// Created by tseyler on 3/22/16.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <core/protocol/c4soap/c4soap_getdevicebyinterface.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            bool
            c4soap_getdevicebyinterface::is_response(const c4soap_message& msg, unsigned long seq)
            {
                return (boost::equal(msg.c4soap_name(), c4soap_cmd_getdevicesbyinterface) && seq == msg.c4soap_seq());

            }

            c4soap_getdevicebyinterface::c4soap_getdevicebyinterface(const c4soap_message& msg) : c4soap_message(msg),
                                                                                                    id_(0)
            {
                id_ = pt_.get<unsigned long>("c4soap.devices.id");
            }
        }
    }
}

