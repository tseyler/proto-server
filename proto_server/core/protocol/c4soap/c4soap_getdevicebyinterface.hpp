//
//  c4soap_getdevicebyinterface.hpp - c4soap get device by interface class
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SERVER_C4SOAP_GETDEVICEBYINTERFACE_HPP_
#define PROTO_SERVER_C4SOAP_GETDEVICEBYINTERFACE_HPP_

#include <core/protocol/c4soap/c4soap_message.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            using boost::property_tree::ptree;

            class c4soap_getdevicebyinterface : public c4soap_message
            {
            public:

                static bool is_response(const c4soap_message& msg, unsigned long seq); // needs matching seq for a response

                c4soap_getdevicebyinterface(const c4soap_message& msg);
                virtual ~c4soap_getdevicebyinterface()
                {}

                unsigned long c4soap_device_id(void) const { return id_; }

            private:

                unsigned long id_;

            };
        }
    }
}

#endif //PROTO_SERVER_C4SOAP_GETDEVICEBYINTERFACE_HPP_
