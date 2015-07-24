/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>
#include <net_data.hpp>



TEST(to_string_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    std::string expected(hello);
    std::string actual = hello_data.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST(string_data_test)
{
    net_data hello_data("Hello World!");
    std::string expected("Hello World!");
    std::string actual = hello_data.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST(clone_test)
{
   char hello[] = "Hello world!";
   net_data hello_data(hello, strlen(hello), data_text);
   char test[] = "  This is a test";
   net_data copy_data(test, strlen(test), data_text);
   hello_data.clone(copy_data);
   std::string expected(test);
   std::string actual = hello_data.to_string();
   CHECK_EQUAL( expected, actual );
}

TEST(append_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    net_data copy_data(test, strlen(test), data_text);
    hello_data.append(copy_data);
    hello_data.data_type(data_text); // change back to text
    std::string expected("Hello world!  This is a test");
    std::string actual = hello_data.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST(equals_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    net_data copy_data(hello, strlen(hello), data_text);
    bool actual = hello_data.equals(copy_data);
    CHECK( actual );
}

TEST(equal_operator_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    net_data equal_data = hello_data;
    std::string expected(hello);
    std::string actual = equal_data.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST(concat_operator_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    net_data copy_data(test, strlen(test), data_text);
    hello_data += copy_data;
    hello_data.data_type(data_text); // change back to text
    std::string expected("Hello world!  This is a test");
    std::string actual = hello_data.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST(plus_operator_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    net_data copy_data(test, strlen(test), data_text);
    net_data sum_data = hello_data + copy_data;
    sum_data.data_type(data_text); // change back to text
    std::string expected("Hello world!  This is a test");
    std::string actual = sum_data.to_string();
    CHECK_EQUAL( expected, actual );
}

TEST(equals_operator_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    net_data copy_data(hello, strlen(hello), data_text);
    bool actual = (hello_data == copy_data);
    CHECK( actual );
}

TEST(not_equals_operator_test)
{
    char hello[] = "Hello world!";
    net_data hello_data(hello, strlen(hello), data_text);
    char test[] = "  This is a test";
    net_data copy_data(test, strlen(test), data_text);
    bool actual = (hello_data != copy_data);
    CHECK( actual );
}
