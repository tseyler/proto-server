/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/


#include <core/protocol/net_parse_routines.hpp>
#include <gtest/gtest.h>

using namespace proto_net::protocol;


TEST(NetParseRoutinesTest, search_pattern_test)
{
     std::string str("This is a test");
     std::string pat("is");
     EXPECT_TRUE( search_pattern(str, pat) );
}

TEST(NetParseRoutinesTest, search_pattern_count_test)
{
     std::string str("This is a test");
     std::string pat("is");
     size_t expected = 2;
     size_t actual;
     search_pattern(str, pat, actual);
     EXPECT_EQ( expected, actual );
}

TEST(NetParseRoutinesTest, search_pattern_matches_test)
{
     std::string str("This is a test");
     std::string pat(".s");
     matches_t matches;
     search_pattern(str, pat, matches);
     size_t expected = 3;
     EXPECT_EQ( expected, matches.size() );
     if (matches.size() == 3)  // test contents
     {
         std::string expected_string("es");
         EXPECT_EQ( expected_string, matches[2] );
     }
}

TEST(NetParseRoutinesTest, match_pattern_test)
{
    std::string str("   This is a test");
    std::string pat("^\\s+.*");
    EXPECT_TRUE( match_pattern(str, pat) );
}

TEST(NetParseRoutinesTest, match_pattern_matches_test)
{
    std::string str("   This is a test");
    std::string pat("^\\s+(.*)");
    matches_t matches;
    match_pattern(str, pat, matches);
    size_t expected = 2;
    EXPECT_EQ( expected, matches.size() );
    if (matches.size() == 2)  // test contents
    {
	 std::string expected_string("This is a test");
	 EXPECT_EQ( expected_string, matches[1] );
    }
}

TEST(NetParseRoutinesTest, replace_pattern_test)
{
    std::string str("This is a test");
    std::string pat("This");
    std::string rep_str("That");
    std::string expected("That is a test");
    EXPECT_EQ( expected, replace_pattern(str, pat, rep_str) );
}

TEST(NetParseRoutinesTest, trim_front_test)
{
    std::string actual("   This is a test");
    std::string expected("This is a test");
    EXPECT_EQ( expected, trim_front(actual) );
}

TEST(NetParseRoutinesTest, trim_back_test)
{
     std::string actual("This is a test    ");
     std::string expected("This is a test");
     EXPECT_EQ( expected, trim_back(actual) );
}

TEST(NetParseRoutinesTest, trim_test)
{
     std::string actual("       This is a test    ");
     std::string expected("This is a test");
     EXPECT_EQ( expected, trim(actual) );
}

TEST(NetParseRoutinesTest, split_test)
{
    std::string str("This is a test");
    matches_t matches;
    split(str, matches);
    std::string expected("test");
    EXPECT_EQ( expected, matches[3] );
}

TEST(NetParseRoutinesTest, split_sep_test)
{
    std::string str("http://www.google.com");
    std::string sep(":/");
    matches_t matches;
    split(str, sep, matches);
    std::string expected("www.google.com");
    EXPECT_EQ( expected, matches[1] );
}
