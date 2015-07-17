/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>
#include <http/http_constants.hpp>
#include <http/http_parse_routines.hpp>

using namespace proto_http;
using namespace net_proto;

struct test_http_parse_routines_fixture
{
    test_http_parse_routines_fixture()
	{
	    std::stringstream ss_get_request;

	    ss_get_request << "GET /articles/hoho.htm HTTP/1.1" << crlf;
	    ss_get_request << "Cache-Control: max-age=3600, must-revalidate" << crlf;
	    ss_get_request << "Accept: image/gif" << crlf;
	    ss_get_request << "Accept-Language: ko,en-us;q=0.5" << crlf;
	    ss_get_request << "User-Agent: Mozilla/4.0 (compatible; MSIE 5.5; Windows NT 5.0)" << crlf;
	    ss_get_request << "Host: bpastudio.csudh.edu" << crlf;
	    ss_get_request << crlf;

	    get_request_http_ = ss_get_request.str();

	    request_headers_.add_http_headers("request", http_header_fields());
	    request_headers_.add_http_headers("general", http_header_fields());
	    request_headers_.add_http_headers("entity", http_header_fields());

	    std::stringstream ss_get_response;

	    ss_get_response << "HTTP/1.1 200 OK" << crlf;
	    ss_get_response << "Date: Tue, 25 Sep 2012 18:13:00 GMT" << crlf;
	    ss_get_response << "Content-Type: text/html" << crlf;
	    ss_get_response << "Content-Length: 1354" << crlf;
	    ss_get_response << crlf;

	    get_response_http_ = ss_get_response.str();

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

    ~test_http_parse_routines_fixture()
	{
	    delete formed_post_data_;
	}

    net_data* formed_post_data_;
    std::string get_request_http_;
    http_headers request_headers_;
    std::string get_response_http_;
    http_headers response_headers_;
};

TEST_FIXTURE(test_http_parse_routines_fixture, find_crlf_test)
{
    size_t expected = 31;
    size_t actual = find_crlf(get_request_http_, 0);
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_parse_routines_fixture, find_line_test)
{
    std::string expected = "GET /articles/hoho.htm HTTP/1.1";
    std::string actual;
    size_t next_pos = find_line(get_request_http_, actual, 0);
    CHECK_EQUAL( expected, actual );
    size_t expect_pos = 33;
    CHECK_EQUAL( expect_pos, next_pos );
}


TEST_FIXTURE(test_http_parse_routines_fixture, tokenize_line_test)
{
    size_t expected(3);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t line_tokens;
    CHECK_EQUAL( expected, tokenize_line(lines[0], line_tokens) );
}

TEST_FIXTURE(test_http_parse_routines_fixture, get_header_field_lines_test)
{
    size_t expected(5);
    lines_t lines;
    get_lines(get_request_http_, lines);
    lines_t header_field_lines;
    size_t actual = get_header_field_lines(lines, header_field_lines);
    CHECK_EQUAL( expected, actual );
    std::string expected_host = "Host: bpastudio.csudh.edu";
    std::string actual_host = header_field_lines[4];
    CHECK_EQUAL( expected_host, actual_host );
}

TEST_FIXTURE(test_http_parse_routines_fixture, message_body_test)
{
    size_t expected = formed_post_data_->data_size() - 27;
    size_t actual = message_body_position(*formed_post_data_);
    CHECK_EQUAL( expected, actual );
    net_data http_data(formed_post_data_->data(), actual, data_text);
    char* body = formed_post_data_->data() + actual;
    size_t body_size = formed_post_data_->data_size() - actual;
    net_data body_data(body, body_size);
}

TEST_FIXTURE(test_http_parse_routines_fixture, tokenize_header_field_test)
{
    size_t expected(2);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t header_field_tokens;
    CHECK_EQUAL( expected, tokenize_header_field(lines[2], header_field_tokens) );
    if (header_field_tokens.size() == expected)
    {
	std::string expected_name("Accept");
	std::string expected_value("image/gif");
	CHECK_EQUAL( expected_name, header_field_tokens[0] );
	CHECK_EQUAL( expected_value, header_field_tokens[1] );
    }
}

TEST_FIXTURE(test_http_parse_routines_fixture, validate_request_method_test)
{
    http_parse_result expected(http_parse_success);
    std::string method("GET");
    CHECK_EQUAL( expected, validate_request_method(method) );
}

TEST_FIXTURE(test_http_parse_routines_fixture, validate_request_uri_test)
{
    http_parse_result expected(http_parse_success);
    std::string method("GET");
    std::string uri("/articles/hoho.htm");
    CHECK_EQUAL( expected, validate_request_uri(uri, method) );
    uri = "/";
    CHECK_EQUAL( expected, validate_request_uri(uri, method) );
}

TEST_FIXTURE(test_http_parse_routines_fixture, validate_http_version_test)
{
    http_parse_result expected(http_parse_success);
    std::string http_version("HTTP/1.1");
    CHECK_EQUAL( expected, validate_http_version(http_version) );
}

TEST_FIXTURE(test_http_parse_routines_fixture, validate_request_line_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t request_line_tokens;
    tokenize_line(lines[0], request_line_tokens);
    CHECK_EQUAL( expected, validate_request_line(request_line_tokens) );
}

TEST_FIXTURE(test_http_parse_routines_fixture, validate_header_field_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t header_field_tokens;
    tokenize_header_field(lines[2], header_field_tokens);
    std::string field_pat("Accept|Accept-Charset|Accept-Encoding");
    CHECK_EQUAL( expected, validate_header_field(header_field_tokens, field_pat) );
} 

TEST_FIXTURE(test_http_parse_routines_fixture, validate_header_fields_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    lines_t header_field_lines;
    get_header_field_lines(lines, header_field_lines);
    http_header_fields http_fields;
    http_parse_result actual = validate_header_fields(header_field_lines, 
						      "request", 
						      http_fields);
    CHECK_EQUAL( expected, actual);
    size_t expected_size(4);
    CHECK_EQUAL( expected_size, http_fields.size() );
    http_fields.clear();
    actual = validate_header_fields(header_field_lines, 
				    "general", 
				    http_fields);
    expected_size = 1;
    CHECK_EQUAL( expected_size, http_fields.size() );
} 

TEST_FIXTURE(test_http_parse_routines_fixture, validate_http_headers_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    lines_t header_field_lines;
    get_header_field_lines(lines, header_field_lines);
    http_parse_result actual = validate_http_headers(header_field_lines, request_headers_);
    CHECK_EQUAL( expected, actual );
    http_header_fields http_fields = request_headers_["request"];
    size_t expected_size(4);
    CHECK_EQUAL( expected_size, http_fields.size() );
    http_fields = request_headers_["general"];
    expected_size = 1;
    CHECK_EQUAL( expected_size, http_fields.size() );
} 

TEST(validate_status_code)
{
    http_parse_result expected(http_parse_success);
    http_parse_result actual = validate_status_code("200");
    CHECK_EQUAL( expected, actual );
    expected = http_status_code_error;
    actual = validate_status_code("600");
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_parse_routines_fixture, validate_status_line_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_response_http_, lines);
    matches_t status_line_tokens;
    tokenize_line(lines[0], status_line_tokens);
    CHECK_EQUAL( expected, validate_status_line(status_line_tokens) );
}
