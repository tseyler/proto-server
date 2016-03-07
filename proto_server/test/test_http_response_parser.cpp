/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_response_parser.hpp>
#include <gtest/gtest.h>

using namespace proto_net::data;
using namespace proto_net::protocol;
using namespace proto_net::protocol::http;


class HttpResponseParserTest : public ::testing::Test
{
protected:

    HttpResponseParserTest() : formed_response_data_(0)
	{
	    const char response[] = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: 27\r\n"
        "Content-Type: text/xml\r\n"
		"\r\n"
		"userid=joe&password=guessme";
	    formed_response_data_ = new proto_net_string_data(response);
	}

    ~HttpResponseParserTest()
	{
	    delete formed_response_data_;
	}

    proto_net_string_data* formed_response_data_;
};

TEST_F(HttpResponseParserTest, protocol_parse_test)
{
    http_response_parser parser;
    proto_net_string_data data = *formed_response_data_;
    http_response_message parsed;
    http_parse_result expected(http_parse_success);
    EXPECT_EQ( expected, parser.protocol_parse(data, parsed) );
}

TEST_F(HttpResponseParserTest, protocol_form_test)
{
    http_response_parser parser;
    proto_net_string_data data = *formed_response_data_;
    http_response_message parsed;
    parser.protocol_parse(data, parsed);
    std::string parsed_str = parsed.to_string();
    proto_net_string_data formed_data;
    parser.protocol_form(parsed, formed_data);
    std::string data_str = data.to_string();
    std::string formed_str = formed_data.to_string();
    EXPECT_TRUE( (data == formed_data) );
}
