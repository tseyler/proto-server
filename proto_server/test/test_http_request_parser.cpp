/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_request_parser.hpp>
#include <gtest/gtest.h>

using namespace proto_net::data;
using namespace proto_net::protocol;
using namespace proto_net::protocol::http;

class HttpRequestParserTest : public ::testing::Test
{
protected:

    HttpRequestParserTest() : formed_post_data_(0)
	{
	    const char post[] = 
		"POST /cgi/bin/post.html HTTP/1.1\r\n"
		"Host: postitsoftware.com\r\n"
		"User-Agent: Mozilla/4.0\r\n"
		"Content-Length: 27\r\n"
		"Content-Type: application/x-www-form-urlencode\r\n"
		"\r\n"
		"userid=joe&password=guessme";

	    formed_post_data_ = new proto_net_string_data(post);
	}

    ~HttpRequestParserTest()
	{
	    delete formed_post_data_;
	}

    proto_net_string_data* formed_post_data_;
};

TEST_F(HttpRequestParserTest, protocol_parse_test)
{
    http_request_parser parser;
    proto_net_string_data data = *formed_post_data_;
    http_request_message parsed;
    http_parse_result expected(http_parse_success);
    EXPECT_EQ( expected, parser.protocol_parse(data, parsed) );
}

TEST_F(HttpRequestParserTest, protocol_form_test)
{
    http_request_parser parser;
    proto_net_string_data data = *formed_post_data_;
    http_request_message parsed;
    parser.protocol_parse(data, parsed);
    proto_net_string_data formed_data;
    parser.protocol_form(parsed, formed_data);
	std::string data_str = data.to_string();
	std::string formed_str = formed_data.to_string();
    EXPECT_TRUE( (data == formed_data) );
}

