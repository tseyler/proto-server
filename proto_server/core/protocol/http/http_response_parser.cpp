/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string>
#include <iostream>
#include <sstream>
#include <core/protocol/net_parse_routines.hpp>
#include <core/protocol/http/http_parse_routines.hpp>
#include <core/protocol/http/http_response_parser.hpp>

namespace proto_net
{
    using namespace data;

    namespace protocol
    {
        namespace http
        {
            http_parse_result
            http_response_parser::protocol_parse(const proto_net_string_data &formed, http_response_message &parsed)
            {
                // Step 1: get http header
                size_t pos = message_body_position(formed);
                proto_net_data http_header(formed.data(), pos, data_text); // pos is size of header
                // Step 2: convert to lines
                lines_t lines;
                get_lines(http_header.to_string(), lines);
                // Step 3: validate
                http_parse_result res = validate_http_response(lines, parsed);
                // Step 4: add the message body if we validated the header
                if (HTTP_PARSE_SUCCEEDED(res))
                {
                    char* msg_body = formed.data() + pos; // offset ptr to message body
                    proto_net_string_data msg_data(msg_body);
                    parsed.body(msg_data);
                }

                return res;
            }

            http_parse_result
            http_response_parser::protocol_form(const http_response_message &parsed, proto_net_string_data &formed)
            {
                formed = parsed.to_net_data();

                return http_parse_success;
            }

            http_parse_result
            http_response_parser::validate_http_response(const lines_t &lines, http_response_message &parsed)
            {
                http_parse_result res(http_parse_success);
                // 6.1 Status-Line  Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF

                matches_t status_line_tokens; // http_version, status_code
                tokenize_line(lines[0], status_line_tokens); // needs to be first line
                res = validate_status_line(status_line_tokens);
                if (HTTP_PARSE_SUCCEEDED(res))
                {
                    parsed.http_version(status_line_tokens[0]); // http version
                    // get the status code as an int
                    std::stringstream ss(status_line_tokens[1]); // second token is the status code
                    int code(0);
                    ss >> code; // this converts to an int
                    http_status_code &status_code = parsed.get_status_code();
                    status_code.status_code(code);
                    // status line validated so update parsed
                    lines_t header_field_lines;    // get header field lines
                    get_header_field_lines(lines, header_field_lines); // if we have header fields
                    if (header_field_lines.size() > 0)
                        res = validate_http_headers(header_field_lines, parsed.get_headers());
                }

                return res;
            }
        }
    }
}
