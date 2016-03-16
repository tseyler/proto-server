//
// Created by tseyler on 3/16/16.
//

#ifndef C4SOAP_MESSAGE_HPP_
#define C4SOAP_MESSAGE_HPP_

#include <sstream>

namespace proto_net
{
    namespace protocol
    {
        namespace c4soap
        {
            class c4soap_message
            {
            public:

                // this is how you begin a c4soap message
                static void begin_c4soap_message(std::stringstream& ss, const std::string& cmd, int& seq);

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
                virtual ~c4soap_message();

                std::string to_string(void);

            private:



            protected:

                std::string name_;
                unsigned long seq_;
            };
        }
    }
}

#endif //C4SOAP_MESSAGE_HPP_
