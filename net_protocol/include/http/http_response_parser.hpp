/*
<boilerplate>



</boilerplate>
*/

#ifndef HTTP_RESPONSE_PARSER_HPP_
#define HTTP_RESPONSE_PARSER_HPP_

#include <net_protocol.hpp>
#include <http/http_parse_routines.hpp>
#include <http/http_response_message.hpp>

namespace proto_http
{
    class http_response_parser : public net_proto::net_protocol<http_response_message,
								http_parse_result>
    {
    public:

	// this parses a well-formed message.  Returns zero if successful
	virtual http_parse_result protocol_parse(const net_data& formed, 
						 http_response_message& parsed);
	// this forms a well-formed message.  Returns zero if successful 
	virtual http_parse_result protocol_form(const http_response_message& parsed, 
						net_data& formed);

    protected:

	virtual http_parse_result validate_http_response(const lines_t& lines,
							 http_response_message& parsed);

    };

}

#endif
