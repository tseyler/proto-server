//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <core/protocol/c4soap/c4soap_getdevicebyinterface.hpp>
#include "proto_logger.hpp"

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
                try
                {
                    id_ = pt_.get<unsigned long>("c4soap.devices.id");
                }
                catch (boost::property_tree::ptree_error& e)
                {
                    id_ = 0;
                    std::stringstream msg;
                    msg << "c4soap_getdevicebyinterface::c4soap_getdevicebyinterface: Unable to get the device ID: " << e.what();
                    PROTO_LOG_ERROR( msg );
                }
            }
        }
    }
}

