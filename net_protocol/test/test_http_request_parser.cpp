/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string.h>
#include <string>
#include <UnitTest++.h>
#include <unit_test.h>
#include <http/http_request_parser.hpp>

using namespace proto_http;

struct test_http_request_parser_fixture
{
    test_http_request_parser_fixture() : formed_post_data_(0)
	{
	    const char post[] = 
		"POST /cgi/bin/post.html HTTP/1.1\r\n"
		"Host: darkhorsesoftware.com\r\n"
		"User-Agent: Mozilla/4.0\r\n"
		"Content-Length: 27\r\n"
		"Content-Type: application/x-www-form-urlencode\r\n"
		"\r\n"
		"userid=joe&password=guessme";
	    size_t l = strlen(post);
	    formed_post_data_ = new net_data(post, l);
	}

    ~test_http_request_parser_fixture()
	{
	    delete formed_post_data_;
	}

    net_data* formed_post_data_;
};

TEST_FIXTURE(test_http_request_parser_fixture, protocol_parse_test)
{
    http_request_parser parser;
    net_data data = *formed_post_data_;
    http_request_message parsed;
    http_parse_result expected(http_parse_success);
    CHECK_EQUAL( expected, parser.protocol_parse(data, parsed) );
}

TEST_FIXTURE(test_http_request_parser_fixture, protocol_form_test)
{
    http_request_parser parser;
    net_data data = *formed_post_data_;
    http_request_message parsed;
    parser.protocol_parse(data, parsed);
    net_data copy_data;
    parser.protocol_form(parsed, copy_data);
    CHECK( (data == copy_data) );
}
