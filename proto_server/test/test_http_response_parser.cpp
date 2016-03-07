/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string.h>
#include <string>
//#include <UnitTest++.h>
//#include <unit_test.h>
//#include <http/http_response_parser.hpp>
#include <gtest/gtest.h>

/*
using namespace proto_http;

struct test_http_response_parser_fixture
{
    test_http_response_parser_fixture() : formed_response_data_(0)
	{
	    const char response[] = 
		"HTTP/1.1 200 OK\r\n"
		"Host: darkhorsesoftware.com\r\n"
		"Content-Type: application/x-www-form-urlencode\r\n"
		"Content-Length: 27\r\n"
		"\r\n"
		"userid=joe&password=guessme";
	    size_t l = strlen(response);
	    formed_response_data_ = new net_data(response, l);
	}

    ~test_http_response_parser_fixture()
	{
	    delete formed_response_data_;
	}

    net_data* formed_response_data_;
};

TEST_FIXTURE(test_http_response_parser_fixture, protocol_parse_test)
{
    http_response_parser parser;
    net_data data = *formed_response_data_;
    http_response_message parsed;
    http_parse_result expected(http_parse_success);
    CHECK_EQUAL( expected, parser.protocol_parse(data, parsed) );
}

TEST_FIXTURE(test_http_response_parser_fixture, protocol_form_test)
{
    http_response_parser parser;
    net_data data = *formed_response_data_;
    http_response_message parsed;
    parser.protocol_parse(data, parsed);
    net_data copy_data;
    parser.protocol_form(parsed, copy_data);
//    CHECK( (data == copy_data) );
}
*/