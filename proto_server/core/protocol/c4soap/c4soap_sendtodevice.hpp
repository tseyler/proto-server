//
// Created by tseyler on 3/22/16.
//

#ifndef PROTO_SERVER_C4SOAP_SENDTODEVICE_HPP_
#define PROTO_SERVER_C4SOAP_SENDTODEVICE_HPP_

#include <core/protocol/c4soap/c4soap_message.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            using boost::property_tree::ptree;

            class c4soap_sendtodevice : public c4soap_message
            {
            public:

                static bool is_response(const c4soap_message& msg, unsigned long seq); // needs matching seq for a response

                c4soap_sendtodevice(const c4soap_message& msg, const std::string& device_command);
                virtual ~c4soap_sendtodevice()
                {}

                std::string c4soap_device_commnd(void) const { return device_command_; }

            protected:

                std::string device_command_;
            };
        }
    }
}
#endif //PROTO_SERVER_C4SOAP_SENDTODEVICE_HPP_
