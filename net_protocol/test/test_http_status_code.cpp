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
#include <http/http_status_code.hpp>

using namespace proto_http;


TEST(get_status_code_test)
{
    http_status_code sc;
    int expected(400);
    int actual = sc.status_code();
    CHECK_EQUAL( expected, actual );
}

TEST(set_status_code_test)
{
    http_status_code sc;
    int expected(410);
    sc.status_code(410);
    int actual = sc.status_code();
    CHECK_EQUAL( expected, actual );
}

TEST(code_class_test)
{
    http_status_code sc;
    status_code_class expected(code_class_client_error);
    status_code_class actual = sc.code_class();
    CHECK_EQUAL( expected, actual );
}

TEST(reason_phrase_test)
{
    http_status_code sc;
    std::string expected("Bad Request");
    std::string actual = sc.reason_phrase();
    CHECK_EQUAL( expected, actual );
}

TEST(status_code_to_string_test)
{
    http_status_code sc;
    std::string expected("400 Bad Request");
    std::string actual = sc.to_string();
    CHECK_EQUAL( expected, actual );
}
