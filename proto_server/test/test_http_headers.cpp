/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_headers.hpp>

#include <gtest/gtest.h>


using namespace proto_net::protocol::http;

class HttpHeadersTest : public ::testing::Test
{
protected:

    HttpHeadersTest(): header_fields_(), headers_()
	{
	    init();
	}

    ~HttpHeadersTest()
	{ }

    void init(void)
	{
	    header_fields_.set_header_field("Field_One", "One");
	    header_fields_.set_header_field("Field_Two", "Two");
	    headers_.add_http_headers("Test", header_fields_);
	}

    http_header_fields header_fields_;
    http_headers headers_;
};

TEST_F(HttpHeadersTest, add_http_headers_test)
{
    http_headers hh;
    hh.add_http_headers("Test", header_fields_);
    http_headers_map header_map = hh.headers();
    size_t expected(1);
    EXPECT_EQ( expected, header_map.size() );
}

TEST_F(HttpHeadersTest, remove_http_headers_test)
{

    headers_.remove_http_headers("Test");
    http_headers_map header_map = headers_.headers();
    size_t expected(0);
    EXPECT_EQ( expected, header_map.size() );
}

TEST_F(HttpHeadersTest, get_header_fields_test)
{
    http_header_fields http_fields = headers_.get_header_fields("Test");
    header_fields fields = http_fields.get_header_fields();
    size_t expected(2);
    EXPECT_EQ( expected, fields.size() );
    expected = 0;
    http_fields = headers_["Test_One"];
    fields = http_fields.get_header_fields();
    EXPECT_EQ( expected, fields.size() );
}

TEST_F(HttpHeadersTest, to_string_test)
{
    std::string expected = 
	"Field_One: One\r\n"
	"Field_Two: Two\r\n";
    std::string actual = headers_.to_string();
    EXPECT_EQ( expected, actual );
}