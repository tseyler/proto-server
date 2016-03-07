/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <core/data/proto_net_data.hpp>
#include <gtest/gtest.h>

using namespace proto_net::data;

TEST(ProtoNetDataTest, to_string_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    std::string expected(hello);
    std::string actual = hello_data.to_string();
    EXPECT_EQ( expected, actual );
}


TEST(ProtoNetDataTest, string_data_test)
{
    proto_net_data hello_data("Hello World!");
    std::string expected("Hello World!");
    std::string actual = hello_data.to_string();
    EXPECT_EQ( expected, actual );
}


TEST(ProtoNetDataTest, clone_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    proto_net_data copy_data(test, strlen(test), data_text);
    hello_data.clone(copy_data);
    std::string expected(test);
    std::string actual = hello_data.to_string();
    EXPECT_EQ( expected, actual );
}


TEST(ProtoNetDataTest, append_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    proto_net_data copy_data(test, strlen(test), data_text);
    hello_data.append(copy_data);
    hello_data.data_type(data_text); // change back to text
    std::string expected("Hello world!  This is a test");
    std::string actual = hello_data.to_string();
    EXPECT_EQ( expected, actual );
}


TEST(ProtoNetDataTest, equals_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    proto_net_data copy_data(hello, strlen(hello), data_text);
    bool actual = hello_data.equals(copy_data);
    EXPECT_TRUE( actual );
}


TEST(ProtoNetDataTest, equal_operator_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    proto_net_data equal_data = hello_data;
    std::string expected(hello);
    std::string actual = equal_data.to_string();
    EXPECT_EQ( expected, actual );
}


TEST(ProtoNetDataTest, concat_operator_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    proto_net_data copy_data(test, strlen(test), data_text);
    hello_data += copy_data;
    hello_data.data_type(data_text); // change back to text
    std::string expected("Hello world!  This is a test");
    std::string actual = hello_data.to_string();
    EXPECT_EQ( expected, actual );
}


TEST(ProtoNetDataTest, plus_operator_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    proto_net_data copy_data(test, strlen(test), data_text);
    proto_net_data sum_data = hello_data + copy_data;
    sum_data.data_type(data_text); // change back to text
    std::string expected("Hello world!  This is a test");
    std::string actual = sum_data.to_string();
    EXPECT_EQ( expected, actual );
}

TEST(ProtoNetDataTest, equals_operator_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    proto_net_data copy_data(hello, strlen(hello), data_text);
    bool actual = (hello_data == copy_data);
    EXPECT_TRUE( actual );
}

TEST(ProtoNetDataTest, not_equals_operator_test)
{
    char hello[] = "Hello world!";
    proto_net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    proto_net_data copy_data(test, strlen(test), data_text);
    bool actual = (hello_data != copy_data);
    EXPECT_TRUE( actual );
}
