/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/


#include <gtest/gtest.h>
#include <core/protocol/http/http_header_fields.hpp>


using namespace proto_net::protocol::http;

class HttpHeaderFieldsTest : public ::testing::Test
{
protected:

    HttpHeaderFieldsTest()
	{
	    init();
	}

    ~HttpHeaderFieldsTest()
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

TEST_F(HttpHeaderFieldsTest, get_header_field_test)
{
    std::string expected = "One";
    std::string actual;
    EXPECT_TRUE( http_header_fields::get_header_field(header_, "Field_One", actual) );
    EXPECT_EQ( expected, actual );
}


TEST_F(HttpHeaderFieldsTest, empty_field_test)
{
    EXPECT_TRUE( http_header_fields::is_empty_field(header_, "Field_Three") );
}

TEST_F(HttpHeaderFieldsTest, insert_field_test)
{
    std::string expected = "Three";
    std::string actual;
    http_header_fields::insert_header_field(header_, "Field_Three", expected);
    EXPECT_TRUE( http_header_fields::get_header_field(header_, "Field_Three", actual) );
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpHeaderFieldsTest, modify_field_test)
{
    std::string expected = "Won";
    std::string actual;
    EXPECT_TRUE( http_header_fields::modify_header_field(header_, "Field_One", "Won") );
    EXPECT_TRUE( http_header_fields::get_header_field(header_, "Field_One", actual) );
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpHeaderFieldsTest, field_to_string_test)
{
    std::string expected = "Field_One: One\r\n";
    std::string actual = http_header_fields::field_to_string(header_, "Field_One");
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpHeaderFieldsTest, fields_to_string_test)
{
    std::string expected = "Field_One: One\r\nField_Two: Two\r\n";
    std::string actual = http_header_fields::fields_to_string(header_);
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpHeaderFieldsTest, set_header_field_test)
{
    http_header_fields http_header;
    
    http_header.set_header_field("Field_One", "One");
    http_header.set_header_field("Field_Two", "Two");
    header_fields fields = http_header.get_header_fields();
    size_t expected(2);
    EXPECT_EQ( expected, fields.size() );
}

TEST_F(HttpHeaderFieldsTest, header_fields_construct_test)
{
    http_header_fields http_header(header_);
    size_t expected(2);
    EXPECT_EQ( expected, http_header.size() );
}

TEST_F(HttpHeaderFieldsTest, header_fields_clone_test)
{
    http_header_fields http_header;
    http_header.clone(*header_fields_);
    size_t expected(2);
    EXPECT_EQ( expected, http_header.size() );
}

TEST_F(HttpHeaderFieldsTest, header_fields_get_test)
{    
    std::string expected("Two");
    std::string actual;
    EXPECT_TRUE( header_fields_->get_header_field("Field_Two", actual) );
    EXPECT_EQ( expected, actual );
    EXPECT_FALSE( header_fields_->get_header_field("Field_two", actual) );
    expected = "One";
    actual = (*header_fields_)["Field_One"];
    EXPECT_EQ( expected, actual );
}

TEST_F(HttpHeaderFieldsTest, header_fields_set_test)
{    
    std::string expected("two");
    header_fields_->set_header_field("Field_Two", "two");
    std::string actual = (*header_fields_)["Field_Two"];
    EXPECT_EQ( expected, actual  );
    expected = "Three";
    header_fields_->set_header_field("Field_Three", "Three");
    actual = (*header_fields_)["Field_Three"];
    EXPECT_EQ( expected, actual  );
}
