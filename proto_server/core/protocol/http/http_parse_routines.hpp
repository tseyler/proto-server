//
//  http_parse_routines.hpp - parsing routines for HTTP messages
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef HTTP_PARSE_ROUTINES_HPP_
#define HTTP_PARSE_ROUTINES_HPP_

#include <string>
#include <vector>
#include <core/data/proto_net_string_data.hpp>
#include <core/protocol/net_parse_routines.hpp>
#include <core/protocol/http/http_headers.hpp>

#define HTTP_PARSE_SUCCEEDED( r ) (r == http::http_parse_success)

namespace proto_net
{
	using namespace data;

	namespace protocol
	{
		namespace http
		{
			typedef std::vector<std::string> lines_t;
			typedef lines_t::iterator lines_t_iterator;
			typedef lines_t::const_iterator lines_t_const_iterator;

			typedef enum
			{
				http_uninitialized_error = -1,
				http_parse_success,
				http_parse_internal_error,
				http_format_error,
				http_request_method_error,
				http_uri_error,
				http_version_error,
				http_header_field_error,
				http_status_code_error,
			} http_parse_result;

			// find the end of the line (beginning of \r\n) or return std::string::npos
			size_t find_crlf(const std::string &str, size_t pos);

			// find the line and return as out param.  Return start of next line
			size_t find_line(const std::string &str, std::string &line, size_t pos);

			// builds a collection of http header lines.  Returns number of lines
			size_t get_lines(const std::string &http, lines_t &lines);

			// builds a collection of header field lines
			size_t get_header_field_lines(const lines_t &http_lines, lines_t &header_field_lines);

			// return position of start of body
			size_t message_body_position(const proto_net_string_data& data);

			// tokenize routines
			size_t tokenize_http_line(const std::string line, matches_t &tokens);

			size_t tokenize_header_field(const std::string line, matches_t &tokens);

			// validate routines

			// validate request method
			http_parse_result validate_request_method(const std::string method);

			// validate request uri
			http_parse_result validate_request_uri(const std::string &uri, const std::string &method);

			// validate http version
			http_parse_result validate_http_version(const std::string &http_version);

			// validate request line
			http_parse_result validate_request_line(matches_t &tokens);

			// validate header field
			http_parse_result validate_header_field(matches_t &tokens, const std::string &field_name_pat);

			// validate header fields by category
			http_parse_result validate_header_fields(const lines_t &lines, const std::string &category,
													 http_header_fields &http_fields);

			// validate http headers
			http_parse_result validate_http_headers(const lines_t &lines, http_headers &headers);

			// validate status code
			http_parse_result validate_status_code(const std::string &status_code);

			// validate status line
			http_parse_result validate_status_line(matches_t &tokens);
		}
	}
}

#endif
