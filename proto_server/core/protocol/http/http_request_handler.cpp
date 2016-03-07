/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string.h>
#include <sstream>
#include <core/protocol/http/http_request_handler.hpp>

const char ok_html[] = "<html><body><h1>HTTP/1.1 200 OK</h1></body></html>";
const char bad_request_html[] = "<html><body><h1>HTTP/1.1 400 Bad Request</h1></body></html>";

namespace proto_net
{
    using namespace data;

    namespace protocol
    {
        namespace http
        {

            http_response_message
            http_request_handler::form_response(int code, const proto_net_string_data& http_content, const std::string &message_type)
            {
                http_status_code status_code(code);
                http_response_message response(status_code);

                response.body(http_content);  //set the content to http_content
                // adjust message content type and size
                http_header_fields entity_fields;
                entity_fields.set_header_field("Content-Type", message_type);
                std::stringstream ss;
                ss << http_content.data_size();
                entity_fields.set_header_field("Content-Length", ss.str());
                http_headers &response_headers = response.get_headers();
                response_headers.add_http_headers("entity", entity_fields);

                return response;
            }

            http_method
            enumerate_method(const std::string &method)
            {
                http_method val(http_invalid_method);

                if (method == "OPTIONS")
                    val = http_options_method;
                if (method == "GET")
                    val = http_get_method;
                if (method == "HEAD")
                    val = http_head_method;
                if (method == "POST")
                    val = http_post_method;
                if (method == "PUT")
                    val = http_put_method;
                if (method == "DELETE")
                    val = http_delete_method;
                if (method == "TRACE")
                    val = http_trace_method;
                if (method == "CONNECT")
                    val = http_connect_method;

                return val;
            }

            http_request_result
            int_to_request_result(int code)
            {
                http_request_result result(bad_request);

                if (code >= 200 && code < 300)
                    result = ok_request;

                return result;
            }

            http_request_handler::http_request_handler(int status_code /*= 200*/) : status_code_(status_code)
            { }

            http_request_result
            http_request_handler::handle_request(const http_request_message &request, http_response_message &response)
            {
                http_request_result result = int_to_request_result(status_code_);

                switch (result)
                {
                    case ok_request:

                        form_ok_request_response(request, response);
                        break;
                    case bad_request:

                        form_bad_request_response(request, response);
                        break;
                }

                return int_to_request_result(status_code_);
            }

            void
            http_request_handler::form_ok_request_response(const http_request_message &request,
                                                           http_response_message &response)
            {
                switch (enumerate_method(request.method()))
                {
                    case http_invalid_method:
                    case http_options_method:
                    case http_post_method:
                    case http_put_method:
                    case http_delete_method:
                    case http_trace_method:
                    case http_connect_method:
                    case http_head_method:

                        form_bad_request_response(request, response);
                        break;
                    case http_get_method:
                    {
                        proto_net_string_data message_ok(ok_html);
                        response = form_response(status_code_, message_ok, "text/html");
                    }
                        break;
                }
            }

            void
            http_request_handler::form_bad_request_response(const http_request_message &request,
                                                            http_response_message &response)
            {
                status_code_ = 400; // bad request
                proto_net_string_data message_bad_request(bad_request_html);
                response = form_response(status_code_, message_bad_request, "text/html");
            }
        }
    }
}
