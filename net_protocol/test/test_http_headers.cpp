

#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>
#include <http/http_constants.hpp>
#include <http/http_headers.hpp>

using namespace proto_http;

struct test_http_headers_fixture
{
    test_http_headers_fixture(): header_fields_(),
				 headers_()
	{
	    init();
	}

    ~test_http_headers_fixture()
	{

	}

    void init(void)
	{
	    header_fields_.set_header_field("Field_One", "One");
	    header_fields_.set_header_field("Field_Two", "Two");
	    headers_.add_http_headers("Test", header_fields_);
	}

    http_header_fields header_fields_;
    http_headers headers_;
};

TEST_FIXTURE(test_http_headers_fixture, add_http_headers_test)
{
    http_headers hh;
    hh.add_http_headers("Test", header_fields_);
    http_headers_map header_map = hh.headers();
    size_t expected(1);
    CHECK_EQUAL( expected, header_map.size() );
}

TEST_FIXTURE(test_http_headers_fixture, remove_http_headers_test)
{

    headers_.remove_http_headers("Test");
    http_headers_map header_map = headers_.headers();
    size_t expected(0);
    CHECK_EQUAL( expected, header_map.size() );
}

TEST_FIXTURE(test_http_headers_fixture, get_header_fields_test)
{
    http_header_fields http_fields = headers_.get_header_fields("Test");
    header_fields fields = http_fields.get_header_fields();
    size_t expected(2);
    CHECK_EQUAL( expected, fields.size() );
    expected = 0;
    http_fields = headers_["Test_One"];
    fields = http_fields.get_header_fields();
    CHECK_EQUAL( expected, fields.size() );
}
TEST_FIXTURE(test_http_headers_fixture, to_string_test)
{
    std::string expected = 
	"Field_One: One\r\n"
	"Field_Two: Two\r\n";
    std::string actual = headers_.to_string();
    CHECK_EQUAL( expected, actual );
}
