//
//  http_request_handler.hpp - class that represents an HTTP request handler
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef HTTP_REQUEST_HANDLER_HPP_
#define HTTP_REQUEST_HANDLER_HPP_

#include <core/protocol/http/http_request_message.hpp>
#include <core/protocol/http/http_response_message.hpp>

namespace proto_net
{
	using namespace data;

	namespace protocol
	{
		namespace http
		{
			typedef enum
			{
				http_invalid_method,
				http_options_method,
				http_get_method,
				http_head_method,
				http_post_method,
				http_put_method,
				http_delete_method,
				http_trace_method,
				http_connect_method,
			} http_method;

			typedef enum
			{
				ok_request,
				bad_request,
			} http_request_result;

			// enumerate method
			http_method enumerate_method(const std::string &method);

			// convert from status code to a request result
			http_request_result int_to_request_result(int code);

			class http_request_handler
			{
			public:

				static http_response_message form_response(int code, const proto_net_string_data &http_content,
														   const std::string &message_type);

				// status code after validation and before handling
				http_request_handler(int status_code = 200);

				virtual http_request_result handle_request(const http_request_message &request,
														   http_response_message &response);

			protected:

				// 200 OK
				virtual void form_ok_request_response(const http_request_message &request,
													  http_response_message &response);

				// 400 Bad Request
				virtual void form_bad_request_response(const http_request_message &request,
													   http_response_message &response);

			protected:

				int status_code_;
			};
		}
	}
}

#endif

