//
//  http_request_parser.hpp - class that represents an HTTP request parser
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef HTTP_REQUEST_PARSER_HPP_
#define HTTP_REQUEST_PARSER_HPP_

#include <core/protocol/net_protocol.hpp>
#include <core/protocol/http/http_parse_routines.hpp>
#include <core/protocol/http/http_request_message.hpp>

namespace proto_net
{
	using namespace data;

	namespace protocol
	{
		namespace http
		{
			class http_request_parser : public net_protocol<http_request_message, http_parse_result>
			{
			public:

				// this parses a well-formed message.  Returns zero if successful
				virtual http_parse_result protocol_parse(const proto_net_string_data& formed, http_request_message& parsed);

				// this forms a well-formed message.  Returns zero if successful
				virtual http_parse_result protocol_form(const http_request_message& parsed, proto_net_string_data& formed);

			protected:

				virtual http_parse_result validate_http_request(const lines_t& lines, http_request_message& parsed);
			};
		}
	}
}

#endif
