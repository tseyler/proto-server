//
//  c4soap_message.hpp - c4soap message class
//  part of the proto-server library
//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef C4SOAP_MESSAGE_HPP_
#define C4SOAP_MESSAGE_HPP_

#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            using  boost::property_tree::ptree;

            class c4soap_message
            {
            public:

                static const std::string c4soap_cmd_authenticatepassword;
                static const std::string c4soap_cmd_getdevicesbyinterface;
                static const std::string c4soap_cmd_sendtodevice;

                // this is how you begin a c4soap message
                static void begin_c4soap_message(std::stringstream& ss, const std::string& cmd, unsigned long& seq);

                static void begin_c4soap_async_message(std::stringstream& ss, const std::string& cmd, unsigned long& seq);
                // this is how you end a c4soap message
                static void end_c4soap_message(std::stringstream& ss);

                // returns a param where the value is a string:
                // <param name="foo" type="string">bar</param>
                static std::string get_param(const std::string& name, const std::string& type, const std::string& value);

                // returns a param where the value is a string:
                // <param name="foo" type="number">1</param>
                static std::string get_param(const std::string& name, const std::string& type, int value);

                // returns a modified stringstream with a new param with a string value
                static void param(std::stringstream& ss, const std::string& name, const std::string& type, const std::string& value);

                // returns a modified stringstream with a new param with an integer value
                static void param(std::stringstream& ss, const std::string& name, const std::string& type, int value);

                // used in sendToDevice
                static std::string get_param_value(const std::string& name, const std::string& val);

                c4soap_message(const std::string& name, unsigned long seq);
                c4soap_message(const std::string& c4soap_xml);
                c4soap_message(const c4soap_message& msg);
                virtual ~c4soap_message();

                std::string c4soap_name(void) const { return name_; }
                unsigned long c4soap_seq(void) const { return seq_; }
                unsigned long c4soap_result(void) const { return result_; }
                ptree c4soap_ptree(void) const { return pt_; }
                bool from_c4soap(const std::string& c4soap_xml);
                std::string to_c4soap(void);
                bool is_c4soap(void) const { return is_c4soap_; }
                bool is_async(void) const { return is_async_; }
                std::string to_string(void);

                bool node_exists(const std::string& node_name) const;

            protected:

                std::string name_;
                unsigned long seq_;
                unsigned long result_;
                ptree pt_;
                bool is_c4soap_;
                bool is_async_;
            };

            typedef boost::shared_ptr<c4soap_message> c4soap_message_ptr;
        }
    }
}

#endif //C4SOAP_MESSAGE_HPP_
