//
// Created by tseyler on 3/22/16.
//

#ifndef PROTO_SERVER_C4SOAP_STD_GETUSER_HPP_
#define PROTO_SERVER_C4SOAP_STD_GETUSER_HPP_

#include <core/protocol/c4soap/c4soap_sendtodevice.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            using boost::property_tree::ptree;

            class c4soap_std_getuser : public c4soap_sendtodevice
            {
            public:

                static const std::string c4soap_cmd_getuser;

                static bool is_response(const c4soap_sendtodevice& msg, unsigned long seq); // needs matching seq for a response

                c4soap_std_getuser(const c4soap_message& msg);
                virtual ~c4soap_std_getuser ()
                {}

                unsigned long c4soap_device_id(void) const { return id_; }
                std::string c4soap_user(void) const { return user_; }
                std::string c4soap_domain(void) const { return domain_; }
                std::string c4soap_password(void) const { return password_; }

            private:

                unsigned long id_;
                std::string user_;
                std::string domain_;
                std::string password_;
            };
        }
    }
}


#endif //PROTO_SERVER_C4SOAP_STD_GETUSER_HPP_
