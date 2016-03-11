/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_request_parser.hpp>

#include <gtest/gtest.h>

using namespace proto_net::data;
using namespace proto_net::protocol;
using namespace proto_net::protocol::http;

class HttpRequestMessageTest : public ::testing::Test
{
public:

    HttpRequestMessageTest() : req_post_with_body_()
	{
	    req_ = new http_request_message();
	    req_post_ = new http_request_message("POST", "cgi/bin/post.html");
	    const char post[] = 
		"POST /cgi/bin/post.html HTTP/1.1\r\n"
		"Host: postitsoftware.com\r\n"
		"User-Agent: Mozilla/4.0\r\n"
		"Content-Length: 27\r\n"
		"Content-Type: application/x-www-form-urlencode\r\n"
		"\r\n"
		"userid=joe&password=guessme";

	    proto_net_string_data formed_post_data(post);
	    http_request_parser parser;
	    parser.protocol_parse(formed_post_data, req_post_with_body_);

	    str_post_ = post;
	}

    ~HttpRequestMessageTest ()
	{
	    delete req_;
	    delete req_post_;
	}

    http_request_message* req_;
    http_request_message* req_post_;
    http_request_message req_post_with_body_;
    std::string str_post_;
};

TEST_F(HttpRequestMessageTest, init_test)
{
    EXPECT_TRUE( req_ != 0 );
}

TEST_F(HttpRequestMessageTest, method_test)
{
    std::string expected = "GET";
    EXPECT_EQ( expected, req_->method() );
    expected = "OPTIONS";
    req_->method(expected);
    EXPECT_EQ( expected, req_->method() );
}

TEST_F(HttpRequestMessageTest, request_uri_test)
{
    std::string expected = "*";
    EXPECT_EQ( expected, req_->request_uri() );
    expected = "html/index.html";
    req_->request_uri(expected);
    EXPECT_EQ( expected, req_->request_uri() );
}

TEST_F(HttpRequestMessageTest, request_line_test)
{
    std::stringstream ss;
    ss << "POST" << sp <<  "cgi/bin/post.html" << sp << "HTTP/1.1" << crlf;
    std::string expected = ss.str();
    EXPECT_EQ( expected, req_post_->request_line() );
}

TEST_F(HttpRequestMessageTest, to_string_test)
{
    std::string expected = str_post_;
    std::string actual = req_post_with_body_.to_string();
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpRequestMessageTest, clone_test)
{
    http_request_message req_copy;
    std::string expected = "POST";
    req_copy.clone(*req_post_);
    std::string actual = req_copy.method();
    EXPECT_EQ( expected, actual );
    std::stringstream ss;
    ss << "POST" << sp << "cgi/bin/post.html" << sp << "HTTP/1.1" << crlf;
    expected = ss.str();
    EXPECT_EQ( expected, req_copy.request_line() );
}

TEST_F(HttpRequestMessageTest, header_to_string_test)
{
    std::string expected = 		
	"POST /cgi/bin/post.html HTTP/1.1\r\n"
	"Host: postitsoftware.com\r\n"
	"User-Agent: Mozilla/4.0\r\n"
	"Content-Length: 27\r\n"
	"Content-Type: application/x-www-form-urlencode\r\n"
	"\r\n";

    std::string actual = req_post_with_body_.header_to_string();
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpRequestMessageTest, to_net_data_test)
{
    std::string expected = str_post_;
    proto_net_string_data req_data = req_post_with_body_.to_net_data();
    std::string actual = req_data.to_string();
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpRequestMessageTest, content_length_test)
{
    size_t expected(27);
    size_t actual = req_post_with_body_.content_length();
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpRequestMessageTest, message_body_test)
{
    std::string expected("userid=joe&password=guessme");
    std::string actual = req_post_with_body_.body().to_string();
    EXPECT_EQ( expected, actual );
}
