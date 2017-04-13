//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <proto_logger.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <core/protocol/c4soap/c4soap_message.hpp>


namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            unsigned long
            string_to_ulong(const std::string& str_ulong)
            {
                unsigned long ul_val(0UL);
                try
                {
                    ul_val = boost::lexical_cast<unsigned long>(str_ulong);
                }
                catch (const boost::bad_lexical_cast & ex)
                {
                    std::stringstream ss;
                    ss <<  "Bad cast from " << str_ulong << "to an unsigned long.";
                    PROTO_LOG_WARN( ss );
                }

                return ul_val;
            }

            bool
            string_to_bool(const std::string& str_bool)
            {
                return boost::iequals(str_bool, "true") || boost::iequals(str_bool, "1");
            }

            const std::string c4soap_message::c4soap_cmd_authenticatepassword = "AuthenticatePassword";
            const std::string c4soap_message::c4soap_cmd_getdevicesbyinterface = "GetDevicesByInterface";
            const std::string c4soap_message::c4soap_cmd_sendtodevice = "SendToDevice";

            void
            c4soap_message::begin_c4soap_message(std::stringstream& ss, const std::string& cmd, unsigned long& seq)
            {
                ss << "<c4soap name=\"" << cmd << "\" seq=\"" << ++seq << "\">";
            }

            void
            c4soap_message::begin_c4soap_async_message(std::stringstream& ss, const std::string& cmd, unsigned long& seq)
            {
                ss << "<c4soap name=\"" << cmd << "\" seq=\"" << ++seq << "\" async=\"1\">";
            }

            void
            c4soap_message::end_c4soap_message(std::stringstream& ss)
            {
                ss << "</c4soap>";
            }

            std::string
            c4soap_message::get_param(const std::string& name, const std::string& type, const std::string& value)
            {
                std::stringstream ss;
                ss << "<param name=\"" << name << "\" type=\"" << type << "\">";
                ss << value;
                ss << "</param>";

                return ss.str();
            }

            std::string
            c4soap_message::get_param(const std::string& name, const std::string& type, int value)
            {
                std::stringstream ss;
                ss << "<param name=\"" << name << "\" type=\"" << type << "\">";
                ss << value;
                ss << "</param>";

                return ss.str();
            }

            void
            c4soap_message::param(std::stringstream& ss, const std::string& name, const std::string& type, const std::string& value)
            {
                ss << get_param(name, type, value);
            }

            void
            c4soap_message::param(std::stringstream& ss, const std::string& name, const std::string& type, int value)
            {
                ss << get_param(name, type, value);
            }

            std::string
            c4soap_message::get_param_value(const std::string& name, const std::string& val)
            {
                std::stringstream  ss;
                ss << "<param>";
                ss << "<name>" << name << "</name>";
                ss << "<value type=\"string\">";
                ss << "<static>" << val << "</static>";
                ss << "</value>";
                ss << "</param>";

                return ss.str();
            }

            c4soap_message::c4soap_message(const std::string& name, unsigned long seq) : name_(name), seq_(seq),
                                                                                         result_(0), is_c4soap_(false),
                                                                                         is_async_(false)
            {}

            c4soap_message::c4soap_message(const std::string& c4soap_xml) : name_(""), seq_(0), result_(0),
                                                                            is_c4soap_(false), is_async_(false)
            {
                is_c4soap_ = from_c4soap(c4soap_xml);
            }

            c4soap_message::c4soap_message(const c4soap_message& msg) : name_(msg.c4soap_name()), seq_(msg.c4soap_seq()),
                                                                  result_(msg.c4soap_result()), pt_(msg.c4soap_ptree()),
                                                                        is_c4soap_(msg.is_c4soap()), is_async_(msg.is_async())
            {}

            c4soap_message::~c4soap_message()
            {}

            bool
            c4soap_message::from_c4soap(const std::string& c4soap_xml)
            {
                using boost::property_tree::ptree;

                std::stringstream ss;
                ss << c4soap_xml;

                try
                {
                    read_xml(ss, pt_);

                    name_ = node_exists("c4soap.<xmlattr>.name") ? pt_.get<std::string>("c4soap.<xmlattr>.name") : "";
                    seq_  = string_to_ulong(node_exists("c4soap.<xmlattr>.seq") ? pt_.get<std::string>("c4soap.<xmlattr>.seq") : "");
                    result_  = string_to_ulong(node_exists("c4soap.<xmlattr>.result") ? pt_.get<std::string>("c4soap.<xmlattr>.result") : "");
                    is_async_ = string_to_bool(node_exists("c4soap.<xmlattr>.async") ? pt_.get<std::string>("c4soap.<xmlattr>.async") : "0");
                }
                catch (boost::property_tree::xml_parser_error& err)
                {
                    std::stringstream ss;
                    ss << "c4soap_message::from_c4soap parsing error: " << err.message();
                    PROTO_LOG_ERROR( ss );

                    return false;
                }

                return true;
            }

            std::string
            c4soap_message::to_c4soap(void)
            {
                std::string c4soap_xml;

                return c4soap_xml;
            }

            bool
            c4soap_message::node_exists(const std::string& node_name) const
            {
                boost::optional<const ptree&> node = pt_.get_child_optional(node_name);

                return node.is_initialized();
            }
        }
    }
}

