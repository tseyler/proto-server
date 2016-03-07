/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_response_message.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace http
        {
            http_response_message::http_response_message() : http_message(), status_code_(400)
            {
                headers_.add_http_headers("response", http_header_fields());
                headers_.add_http_headers("general", http_header_fields());
                headers_.add_http_headers("entity", http_header_fields());
            }

            http_response_message::http_response_message(const http_status_code &status_code)
                    : http_message(),
                      status_code_(status_code)
            {
                headers_.add_http_headers("response", http_header_fields());
                headers_.add_http_headers("general", http_header_fields());
                headers_.add_http_headers("entity", http_header_fields());
            }

            http_response_message::http_response_message(const http_response_message &copy)
            {
                clone(copy);
            }

            http_response_message &
            http_response_message::operator=(const http_response_message &rhs)
            {
                if (&rhs != this)
                    clone(rhs);

                return *this;
            }

            void
            http_response_message::clone(const http_response_message &copy)
            {
                status_code_ = copy.status_code();
                http_message::clone(copy);
            }

            http_status_code
            http_response_message::status_code(void) const
            {
                return status_code_;
            }

            http_status_code &
            http_response_message::get_status_code(void)
            {
                return status_code_;
            }

            std::string
            http_response_message::http_version(void) const
            {
                return http_message::http_version();
            }

            void
            http_response_message::http_version(const std::string &version)
            {
                http_message::http_version(version);
            }

            http_headers
            http_response_message::headers(void) const
            {
                return http_message::headers();
            }

            http_headers &
            http_response_message::get_headers(void)
            {
                return http_message::get_headers();
            }

            std::string
            http_response_message::status_line(void) const
            {
                std::stringstream ss;
                ss << http_version_ << sp << status_code_.to_string() << crlf;

                return ss.str();
            }

            std::string
            http_response_message::header_to_string(void) const
            {
                std::stringstream ss;
                ss << status_line(); // status line
                ss << http_message::header_to_string();

                return ss.str();
            }
        }
    }
}

