/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_request_handler.hpp>
#include <gtest/gtest.h>

using namespace proto_net::protocol::http;

class HttpRequestHandlerTest : public ::testing::Test
{
protected:

    HttpRequestHandlerTest() : get_req_("GET", "/index.html")
	{
	}

    ~HttpRequestHandlerTest()
	{
	}

    http_request_message get_req_;
};

TEST_F(HttpRequestHandlerTest, handle_request_test)
{
    http_request_handler req_handler; // we are 200 OK
    http_response_message response;
    http_request_result expected(ok_request);
    http_request_result actual = req_handler.handle_request(get_req_, response);
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpRequestHandlerTest, enumerate_method_test)
{
    http_method expected(http_get_method);
    http_method actual = enumerate_method("GET");
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpRequestHandlerTest, int_to_request_result_test)
{
    http_request_result expected(ok_request);
    http_request_result actual = int_to_request_result(202);
    EXPECT_EQ( expected, actual );
}
