/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>
#include <http/http_message.hpp>

using namespace proto_http;

TEST(http_version_test)
{
    http_message msg;
    std::string expected = "HTTP/1.1";
    CHECK_EQUAL( expected, msg.http_version() );
}
