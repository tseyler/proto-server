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
#include <http/http_request_parser.hpp>

using namespace proto_http;

struct test_http_request_message_fixture
{
    test_http_request_message_fixture() : req_post_with_body_()
	{
	    req_ = new http_request_message();
	    req_post_ = new http_request_message("POST", "cgi/bin/post.html");
	    const char post[] = 
		"POST /cgi/bin/post.html HTTP/1.1\r\n"
		"Host: darkhorsesoftware.com\r\n"
		"User-Agent: Mozilla/4.0\r\n"
		"Content-Length: 27\r\n"
		"Content-Type: application/x-www-form-urlencode\r\n"
		"\r\n"
		"userid=joe&password=guessme";
	    size_t l = strlen(post);
	    net_data formed_post_data(post, l);
	    http_request_parser parser;
	    parser.protocol_parse(formed_post_data, req_post_with_body_);
	    net_data& body_data = req_post_with_body_.get_body();
	    body_data.data_type(data_text);

	    str_post_ = post;
	}

    ~test_http_request_message_fixture()
	{
	    delete req_;
	    delete req_post_;
	}

    http_request_message* req_;
    http_request_message* req_post_;
    http_request_message req_post_with_body_;
    std::string str_post_;

};

TEST_FIXTURE(test_http_request_message_fixture, init_test)
{
    CHECK( req_ != 0 );
}

TEST_FIXTURE(test_http_request_message_fixture, method_test)
{
    std::string expected = "GET";
    CHECK_EQUAL( expected, req_->method() );
    expected = "OPTIONS";
    req_->method(expected);
    CHECK_EQUAL( expected, req_->method() );
}

TEST_FIXTURE(test_http_request_message_fixture, request_uri_test)
{
    std::string expected = "*";
    CHECK_EQUAL( expected, req_->request_uri() );
    expected = "html/index.html";
    req_->request_uri(expected);
    CHECK_EQUAL( expected, req_->request_uri() );
}

TEST_FIXTURE(test_http_request_message_fixture, request_line_test)
{
    std::stringstream ss;
    ss << "POST" << sp <<  "cgi/bin/post.html" << sp << "HTTP/1.1" << crlf;
    std::string expected = ss.str();
    CHECK_EQUAL( expected, req_post_->request_line() );
}

TEST_FIXTURE(test_http_request_message_fixture, to_string_test)
{
    std::string expected = str_post_;
    std::string actual = req_post_with_body_.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_request_message_fixture, clone_test)
{
    http_request_message req_copy;
    std::string expected = "POST";
    req_copy.clone(*req_post_);
    std::string actual = req_copy.method();
    CHECK_EQUAL( expected, actual );
    std::stringstream ss;
    ss << "POST" << sp << "cgi/bin/post.html" << sp << "HTTP/1.1" << crlf;
    expected = ss.str();
    CHECK_EQUAL( expected, req_copy.request_line() );
}

TEST_FIXTURE(test_http_request_message_fixture, header_to_string_test)
{
    std::string expected = 		
	"POST /cgi/bin/post.html HTTP/1.1\r\n"
	"Host: darkhorsesoftware.com\r\n"
	"User-Agent: Mozilla/4.0\r\n"
	"Content-Length: 27\r\n"
	"Content-Type: application/x-www-form-urlencode\r\n"
	"\r\n";

    std::string actual = req_post_with_body_.header_to_string();
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_request_message_fixture, to_net_data_test)
{
    std::string expected = str_post_;
    net_data req_data = req_post_with_body_.to_net_data();
    req_data.data_type(data_text);
    std::string actual = req_data.to_string();
    CHECK_EQUAL( expected, actual );
}

