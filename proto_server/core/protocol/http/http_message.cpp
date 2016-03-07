/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_message.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace http
        {
            http_message::http_message() : http_version_("HTTP/1.1"),
                                           headers_(),
                                           message_body_()
            { }

            void
            http_message::clone(const http_message &copy)
            {
                http_version_ = copy.http_version();
                headers_ = copy.headers(); // using http_headers assignment operator
                message_body_ = copy.body();
            }

            std::string
            http_message::http_version(void) const
            {
                return http_version_;
            }

            void
            http_message::http_version(const std::string& version)
            {
                http_version_ = version;
            }

            http_headers
            http_message::headers(void) const
            {
                return headers_;
            }

            http_headers &
            http_message::get_headers(void)
            {
                return headers_;
            }

            std::string
            http_message::header_to_string(void) const
            {
                std::stringstream ss;

                ss << headers_.to_string();
                ss << crlf; // end of header

                return ss.str();
            }

            std::string
            http_message::to_string(void) const
            {
                std::stringstream ss;
                ss << header_to_string() << message_body_.to_string();

                return ss.str();
            }

            proto_net_string_data
            http_message::body(void) const
            {
                return message_body_;
            }

            void
            http_message::body(const proto_net_string_data& data)
            {
                message_body_ = data;
            }

            proto_net_string_data
            http_message::to_net_data(void) const
            {
                std::string header = header_to_string();
                proto_net_string_data header_data(header);

                return header_data + message_body_;
            }
        }
    }
}

