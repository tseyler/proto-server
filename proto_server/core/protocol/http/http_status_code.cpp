//
//  Copyright (c) 2015 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <iostream>
#include <sstream>
#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_status_code.hpp>

namespace proto_net
{
	namespace protocol
	{
		namespace http
		{
			// informational
			const int code_continue = 100;
			const int code_switching_protocols = 101;
			// success
			const int code_ok = 200;
			const int code_created = 201;
			const int code_accepted = 202;
			const int code_non_authoritative_information = 203;
			const int code_no_content = 204;
			const int code_reset_content = 205;
			const int code_partial_content = 206;
			// redirection
			const int code_multiple_choices = 300;
			const int code_moved_permanently = 301;
			const int code_found = 302;
			const int code_see_other = 303;
			const int code_not_modified = 304;
			const int code_use_proxy = 305;
			const int code_temporary_redirect = 307;
			// client error
			const int code_bad_request = 400;
			const int code_unauthorized = 401;
			const int code_payment_required = 402;
			const int code_forbidden = 403;
			const int code_not_found = 404;
			const int code_method_not_allowed = 405;
			const int code_not_acceptable = 406;
			const int code_proxy_authentication_required = 407;
			const int code_request_time_out = 408;
			const int code_conflict = 409;
			const int code_gone = 410;
			const int code_length_required = 411;
			const int code_precondition_failed = 412;
			const int code_request_entity_too_large = 413;
			const int code_request_uri_too_large = 414;
			const int code_unsupported_media_type = 415;
			const int code_requested_range_not_satisfiable = 416;
			const int code_expectation_failed = 417;
			// server error
			const int code_internal_server_error = 500;
			const int code_not_implemented = 501;
			const int code_bad_gateway = 502;
			const int code_service_unavailable = 503;
			const int code_gateway_time_out = 504;
			const int code_http_version_not_supported = 505;

			std::string
			reason_informational(int code)
			{
				std::string reason("Request received, continuing process");

				switch (code)
				{
					case code_continue:

						reason = "Continue";
						break;
					case code_switching_protocols:

						reason = "Switching Protocols";
						break;
				}

				return reason;
			}

			std::string
			reason_success(int code)
			{
				std::string reason("The action was successfully received");

				switch (code)
				{

					case code_ok:

						reason = "OK";
						break;
					case code_created:

						reason = "Created";
						break;
					case code_accepted:

						reason = "Accepted";
						break;
					case code_non_authoritative_information:

						reason = "Non-Authoritative Information";
						break;
					case code_no_content:

						reason = "No Content";
						break;
					case code_reset_content:

						reason = "Reset Content";
						break;
					case code_partial_content:

						reason = "Partial Content";
						break;
				}

				return reason;
			}

			std::string
			reason_redirection(int code)
			{
				std::string reason("Further action must be taken");

				switch (code)
				{
					case code_multiple_choices:

						reason = "Multiple Choices";
						break;
					case code_moved_permanently:

						reason = "Moved Permanently";
						break;
					case code_found:

						reason = "Found";
						break;
					case code_see_other:

						reason = "See Other";
						break;
					case code_not_modified:

						reason = "Not Modified";
						break;
					case code_use_proxy:

						reason = "Use Proxy";
						break;
					case code_temporary_redirect:

						reason = "Temporary Redirect";
						break;
				}

				return reason;
			}

			std::string
			reason_client_error(int code)
			{
				std::string reason("The request contains bad syntax or cannot be fulfilled");

				switch (code)
				{

					case code_bad_request:

						reason = "Bad Request";
						break;
					case code_unauthorized:

						reason = "Unauthorized";
						break;
					case code_payment_required:

						reason = "Payment Required";
						break;
					case code_forbidden:

						reason = "Forbidden";
						break;
					case code_not_found:

						reason = "Not Found";
						break;
					case code_method_not_allowed:

						reason = "Method Not Allowed";
						break;
					case code_not_acceptable:

						reason = "Not Acceptable";
						break;
					case code_proxy_authentication_required:

						reason = "Proxy Authentication Required";
						break;
					case code_request_time_out:

						reason = "Request time-out";
						break;
					case code_conflict:

						reason = "Conflict";
						break;
					case code_gone:

						reason = "Gone";
						break;
					case code_length_required:

						reason = "Length Required";
						break;
					case code_precondition_failed:

						reason = "Precondition Failed";
						break;
					case code_request_entity_too_large:

						reason = "Request Entity Too Large";
						break;
					case code_request_uri_too_large:

						reason = "Request URI Too Large";
						break;
					case code_unsupported_media_type:

						reason = "Unsupported Media Type";
						break;
					case code_requested_range_not_satisfiable:

						reason = "Requested Range Not Satisfiable";
						break;
					case code_expectation_failed:

						reason = "Expectation Failed";
						break;
				}

				return reason;
			}

			std::string
			reason_server_error(int code)
			{
				std::string reason("The server failed to fulfill an apparently valid request");

				switch (code)
				{
					case code_internal_server_error:

						reason = "Internal Server Error";
						break;
					case code_not_implemented:

						reason = "Not Implemented";
						break;
					case code_bad_gateway:

						reason = "Bad Gateway";
						break;
					case code_service_unavailable:

						reason = "Service Unavailable";
						break;
					case code_gateway_time_out:

						reason = "Gateway Time-out";
						break;
					case code_http_version_not_supported:

						reason = "HTTP Version not supported";
						break;
				}

				return reason;
			}

			http_status_code::http_status_code(int code /*= 400*/) : status_code_(code)
			{ }

			http_status_code::http_status_code(const http_status_code &copy) : status_code_(400)
			{
				clone(copy);
			}

			http_status_code &
			http_status_code::operator=(const http_status_code &rhs)
			{
				if (&rhs != this)
					clone(rhs);

				return *this;
			}

			void
			http_status_code::clone(const http_status_code &copy)
			{
				status_code_ = copy.status_code();
			}

			int
			http_status_code::status_code(void) const
			{
				return status_code_;
			}

			void
			http_status_code::status_code(int code)
			{
				status_code_ = code;
			}

			status_code_class
			http_status_code::code_class(void) const
			{
				status_code_class status_class(code_class_bad);

				if (status_code_ > 0 && status_code_ < 600)
					status_class = static_cast<status_code_class>(status_code_ / 100);

				return status_class;
			}

			std::string
			http_status_code::reason_phrase(void) const
			{
				std::string phrase;

				status_code_class scc = code_class();

				switch (scc)
				{
					case code_class_informational:

						phrase = reason_informational(status_code_);
						break;
					case code_class_success:

						phrase = reason_success(status_code_);
						break;
					case code_class_redirection:

						phrase = reason_redirection(status_code_);
						break;
					case code_class_client_error:

						phrase = reason_client_error(status_code_);
						break;
					case code_class_server_error:

						phrase = reason_server_error(status_code_);
						break;
					case code_class_bad:

						phrase = "";
				}

				return phrase;
			}

			std::string
			http_status_code::to_string(void) const
			{
				std::stringstream ss;

				ss << status_code_ << sp << reason_phrase();

				return ss.str();
			}
		}
	}
}

