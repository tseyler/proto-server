/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/


#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>

#include <http/http_header_fields.hpp>


using namespace proto_http;

struct test_http_header_fields_fixture
{
    test_http_header_fields_fixture()
	{
	    init();
	}

    ~test_http_header_fields_fixture()
	{ 
	    delete header_fields_;
	}

    void init(void)
	{
	    header_["Field_One"] = "One";
	    header_["Field_Two"] = "Two";
	    header_fields_ = new http_header_fields(header_);
	}

    header_fields header_;
    http_header_fields* header_fields_;
};

TEST_FIXTURE(test_http_header_fields_fixture, get_header_field_test)
{
    std::string expected = "One";
    std::string actual;
    CHECK( http_header_fields::get_header_field(header_, "Field_One", actual) );
    CHECK_EQUAL( expected, actual );
}


TEST_FIXTURE(test_http_header_fields_fixture, empty_field_test)
{
    CHECK( http_header_fields::is_empty_field(header_, "Field_Three") ); 
}

TEST_FIXTURE(test_http_header_fields_fixture, insert_field_test)
{
    std::string expected = "Three";
    std::string actual;
    http_header_fields::insert_header_field(header_, "Field_Three", expected);
    CHECK( http_header_fields::get_header_field(header_, "Field_Three", actual) );
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_header_fields_fixture, modify_field_test)
{
    std::string expected = "Won";
    std::string actual;
    CHECK( http_header_fields::modify_header_field(header_, "Field_One", "Won") );
    CHECK( http_header_fields::get_header_field(header_, "Field_One", actual) );
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_header_fields_fixture, field_to_string_test)
{
    std::string expected = "Field_One: One\r\n";
    std::string actual = http_header_fields::field_to_string(header_, "Field_One");
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_header_fields_fixture, fields_to_string_test)
{
    std::string expected = "Field_One: One\r\nField_Two: Two\r\n";
    std::string actual = http_header_fields::fields_to_string(header_);
    CHECK_EQUAL( expected, actual );
}

TEST(set_header_field_test)
{
    http_header_fields http_header;
    
    http_header.set_header_field("Field_One", "One");
    http_header.set_header_field("Field_Two", "Two");
    header_fields fields = http_header.get_header_fields();
    size_t expected(2);
    CHECK_EQUAL( expected, fields.size() );
}

TEST_FIXTURE(test_http_header_fields_fixture, header_fields_construct_test)
{
    http_header_fields http_header(header_);
    size_t expected(2);
    CHECK_EQUAL( expected, http_header.size() );
}

TEST_FIXTURE(test_http_header_fields_fixture, header_fields_clone_test)
{
    http_header_fields http_header;
    http_header.clone(*header_fields_);
    size_t expected(2);
    CHECK_EQUAL( expected, http_header.size() );
}

TEST_FIXTURE(test_http_header_fields_fixture, header_fields_get_test)
{    
    std::string expected("Two");
    std::string actual;
    CHECK( header_fields_->get_header_field("Field_Two", actual) );
    CHECK_EQUAL( expected, actual );
    CHECK_FALSE( header_fields_->get_header_field("Field_two", actual) );
    expected = "One";
    actual = (*header_fields_)["Field_One"];
    CHECK_EQUAL( expected, actual );
}

TEST_FIXTURE(test_http_header_fields_fixture, header_fields_set_test)
{    
    std::string expected("two");
    header_fields_->set_header_field("Field_Two", "two");
    std::string actual = (*header_fields_)["Field_Two"];
    CHECK_EQUAL( expected, actual  );
    expected = "Three";
    header_fields_->set_header_field("Field_Three", "Three");
    actual = (*header_fields_)["Field_Three"];
    CHECK_EQUAL( expected, actual  );
}
