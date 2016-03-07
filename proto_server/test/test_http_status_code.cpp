/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/


#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_status_code.hpp>
#include <gtest/gtest.h>

using namespace proto_net::protocol::http;

TEST(StatusCodeTest, get_status_code_test)
{
    http_status_code sc;
    int expected(400);
    int actual = sc.status_code();
    EXPECT_EQ( expected, actual );
}

TEST(StatusCodeTest,set_status_code_test)
{
    http_status_code sc;
    int expected(410);
    sc.status_code(410);
    int actual = sc.status_code();
    EXPECT_EQ( expected, actual );
}

TEST(StatusCodeTest, code_class_test)
{
    http_status_code sc;
    status_code_class expected(code_class_client_error);
    status_code_class actual = sc.code_class();
    EXPECT_EQ( expected, actual );
}

TEST(StatusCodeTest, reason_phrase_test)
{
    http_status_code sc;
    std::string expected("Bad Request");
    std::string actual = sc.reason_phrase();
    EXPECT_EQ( expected, actual );
}

TEST(StatusCodeTest, status_code_to_string_test)
{
    http_status_code sc;
    std::string expected("400 Bad Request");
    std::string actual = sc.to_string();
    EXPECT_EQ( expected, actual );
}
