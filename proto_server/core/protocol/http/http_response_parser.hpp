//
//  http_response_parser.hpp - class that represents an HTTP response parser
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//
#ifndef HTTP_RESPONSE_PARSER_HPP_
#define HTTP_RESPONSE_PARSER_HPP_

#include <core/protocol/net_protocol.hpp>
#include <core/protocol/http/http_parse_routines.hpp>
#include <core/protocol/http/http_response_message.hpp>

namespace proto_net
{
	namespace protocol
	{
		namespace http
		{
			class http_response_parser : public net_protocol<http_response_message, http_parse_result>
			{
			public:

				// this parses a well-formed message.  Returns zero if successful
				virtual http_parse_result protocol_parse(const proto_net_string_data& formed, http_response_message &parsed);

				// this forms a well-formed message.  Returns zero if successful
				virtual http_parse_result protocol_form(const http_response_message& parsed, proto_net_string_data& formed);

			protected:

				virtual http_parse_result validate_http_response(const lines_t &lines, http_response_message& parsed);
			};
		}
	}
}

#endif

