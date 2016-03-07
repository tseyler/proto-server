/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_message.hpp>

#include <gtest/gtest.h>


using namespace proto_net::protocol::http;

TEST(HttpVersionTest, http_version_test)
{
    http_message msg;
    std::string expected = "HTTP/1.1";
    EXPECT_EQ( expected, msg.http_version() );
}
