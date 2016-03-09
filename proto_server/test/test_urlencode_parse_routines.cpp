//
// Created by tseyler on 3/9/16.
//

#include <core/protocol/urlencode/urlencode_parse_routines.hpp>

#include <gtest/gtest.h>

using namespace proto_net::protocol;
using namespace proto_net::protocol::urlencode;


class UrlencodeParserRoutinesTest : public ::testing::Test
{
protected:

    UrlencodeParserRoutinesTest() : url_encoded_("userid=joe&password=guessme")
    {
    }

    ~UrlencodeParserRoutinesTest()
    {

    }

    std::string url_encoded_;

};

TEST_F(UrlencodeParserRoutinesTest, tokenize_urlencode_line_test)
{
    size_t expected(2);
    matches_t tokens;
    size_t actual = tokenize_urlencode_line(url_encoded_, tokens);
    EXPECT_EQ(expected, actual);
}

TEST_F(UrlencodeParserRoutinesTest, tokenize_urlencode_key_value_test)
{
    size_t expected(2);
    matches_t tokens;
    tokenize_urlencode_line(url_encoded_, tokens);
    urlencode_key_values key_values;
    size_t actual = tokenize_urlencode_key_value(tokens, key_values);
    EXPECT_EQ(expected, actual);
    std::string value_1 = key_values["userid"];
    EXPECT_EQ(value_1, "joe");
    std::string value_2 = key_values["password"];
    EXPECT_EQ(value_2, "guessme");
}

