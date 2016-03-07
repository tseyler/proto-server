/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_parse_routines.hpp>

#include <gtest/gtest.h>

using namespace proto_net::data;
using namespace proto_net::protocol;
using namespace proto_net::protocol::http;


class HttpParserRoutinesTest : public ::testing::Test
{
protected:

    HttpParserRoutinesTest()
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
		"Host: postitsoftware.com\r\n"
		"User-Agent: Mozilla/4.0\r\n"
		"Content-Length: 27\r\n"
		"Content-Type: application/x-www-form-urlencode\r\n"
		"\r\n"
		"userid=joe&password=guessme";
	
	    formed_post_data_ = new proto_net_string_data(post);
	}

    ~HttpParserRoutinesTest()
	{
	    delete formed_post_data_;
	}

    proto_net_string_data* formed_post_data_;
    std::string get_request_http_;
    http_headers request_headers_;
    std::string get_response_http_;
    http_headers response_headers_;
};

TEST_F(HttpParserRoutinesTest, find_crlf_test)
{
    size_t expected = 31;
    size_t actual = find_crlf(get_request_http_, 0);
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpParserRoutinesTest, find_line_test)
{
    std::string expected = "GET /articles/hoho.htm HTTP/1.1";
    std::string actual;
    size_t next_pos = find_line(get_request_http_, actual, 0);
    EXPECT_EQ( expected, actual );
    size_t expect_pos = 33;
    EXPECT_EQ( expect_pos, next_pos );
}


TEST_F(HttpParserRoutinesTest, tokenize_line_test)
{
    size_t expected(3);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t line_tokens;
    EXPECT_EQ( expected, tokenize_line(lines[0], line_tokens) );
}

TEST_F(HttpParserRoutinesTest, get_header_field_lines_test)
{
    size_t expected(5);
    lines_t lines;
    get_lines(get_request_http_, lines);
    lines_t header_field_lines;
    size_t actual = get_header_field_lines(lines, header_field_lines);
    EXPECT_EQ( expected, actual );
    std::string expected_host = "Host: bpastudio.csudh.edu";
    std::string actual_host = header_field_lines[4];
    EXPECT_EQ( expected_host, actual_host );
}

TEST_F(HttpParserRoutinesTest, message_body_test)
{
    size_t expected = formed_post_data_->length() - 27;
    size_t actual = message_body_position(*formed_post_data_);
    EXPECT_EQ( expected, actual );
    proto_net_data http_data(formed_post_data_->data(), actual, data_text);
    char* body = formed_post_data_->data() + actual;
    size_t body_size = formed_post_data_->data_size() - actual;
    proto_net_data body_data(body, body_size);
}

TEST_F(HttpParserRoutinesTest, tokenize_header_field_test)
{
    size_t expected(2);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t header_field_tokens;
    EXPECT_EQ( expected, tokenize_header_field(lines[2], header_field_tokens) );
    if (header_field_tokens.size() == expected)
    {
        std::string expected_name("Accept");
        std::string expected_value("image/gif");
        EXPECT_EQ( expected_name, header_field_tokens[0] );
        EXPECT_EQ( expected_value, header_field_tokens[1] );
    }
}

TEST_F(HttpParserRoutinesTest, validate_request_method_test)
{
    http_parse_result expected(http_parse_success);
    std::string method("GET");
    EXPECT_EQ( expected, validate_request_method(method) );
}

TEST_F(HttpParserRoutinesTest, validate_request_uri_test)
{
    http_parse_result expected(http_parse_success);
    std::string method("GET");
    std::string uri("/articles/hoho.htm");
    EXPECT_EQ( expected, validate_request_uri(uri, method) );
    uri = "/";
    EXPECT_EQ( expected, validate_request_uri(uri, method) );
}

TEST_F(HttpParserRoutinesTest, validate_http_version_test)
{
    http_parse_result expected(http_parse_success);
    std::string http_version("HTTP/1.1");
EXPECT_EQ( expected, validate_http_version(http_version) );
}

TEST_F(HttpParserRoutinesTest, validate_request_line_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t request_line_tokens;
    tokenize_line(lines[0], request_line_tokens);
    EXPECT_EQ( expected, validate_request_line(request_line_tokens) );
}

TEST_F(HttpParserRoutinesTest, validate_header_field_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    matches_t header_field_tokens;
    tokenize_header_field(lines[2], header_field_tokens);
    std::string field_pat("Accept|Accept-Charset|Accept-Encoding");
    EXPECT_EQ( expected, validate_header_field(header_field_tokens, field_pat) );
}

TEST_F(HttpParserRoutinesTest, validate_header_fields_test)
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
    EXPECT_EQ( expected, actual);
    size_t expected_size(4);
    EXPECT_EQ( expected_size, http_fields.size() );
    http_fields.clear();
    actual = validate_header_fields(header_field_lines, 
				    "general", 
				    http_fields);
    expected_size = 1;
    EXPECT_EQ( expected_size, http_fields.size() );
}

TEST_F(HttpParserRoutinesTest, validate_http_headers_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_request_http_, lines);
    lines_t header_field_lines;
    get_header_field_lines(lines, header_field_lines);
    http_parse_result actual = validate_http_headers(header_field_lines, request_headers_);
    EXPECT_EQ( expected, actual );
    http_header_fields http_fields = request_headers_["request"];
    size_t expected_size(4);
    EXPECT_EQ( expected_size, http_fields.size() );
    http_fields = request_headers_["general"];
    expected_size = 1;
    EXPECT_EQ( expected_size, http_fields.size() );
}

TEST_F(HttpParserRoutinesTest, validate_status_code)
{
    http_parse_result expected(http_parse_success);
    http_parse_result actual = validate_status_code("200");
    EXPECT_EQ( expected, actual );
    expected = http_status_code_error;
    actual = validate_status_code("600");
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpParserRoutinesTest, validate_status_line_test)
{
    http_parse_result expected(http_parse_success);
    lines_t lines;
    get_lines(get_response_http_, lines);
    matches_t status_line_tokens;
    tokenize_line(lines[0], status_line_tokens);
    EXPECT_EQ( expected, validate_status_line(status_line_tokens) );
}