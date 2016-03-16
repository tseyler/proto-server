//
// Created by tseyler on 3/16/16.
//

#include <core/protocol/c4soap/c4soap_message.hpp>
namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            void
            c4soap_message::begin_c4soap_message(std::stringstream& ss, const std::string& cmd, int& seq)
            {
                ss << "<c4soap name=\"" << cmd << "\" seq=\"" << seq++ << "\">";
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

            c4soap_message::c4soap_message(const std::string& name, unsigned long seq) : name_(name), seq_(seq)
            {}

            c4soap_message::~c4soap_message()
            {}
        }
    }
}

