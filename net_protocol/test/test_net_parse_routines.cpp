

#include <string>
#include <iostream>
#include <sstream>

#include <UnitTest++.h>
#include <unit_test.h>
#include <net_parse_routines.hpp>

using namespace net_proto;


TEST(search_pattern_test)
{
     std::string str("This is a test");
     std::string pat("is");
     CHECK( search_pattern(str, pat) );
}

TEST(search_pattern_count_test)
{
     std::string str("This is a test");
     std::string pat("is");
     size_t expected = 2;
     size_t actual;
     search_pattern(str, pat, actual);
     CHECK_EQUAL( expected, actual );
}


TEST(search_pattern_matches_test)
{
     std::string str("This is a test");
     std::string pat(".s");
     matches_t matches;
     search_pattern(str, pat, matches);
     size_t expected = 3;
     CHECK_EQUAL( expected, matches.size() );
     if (matches.size() == 3)  // test contents
     {
	 std::string expected_string("es");
	 CHECK_EQUAL( expected_string, matches[2] );
     }
}

TEST(match_pattern_test)
{
    std::string str("   This is a test");
    std::string pat("^\\s+.*");
    CHECK( match_pattern(str, pat) );
}

TEST(match_pattern_matches_test)
{
    std::string str("   This is a test");
    std::string pat("^\\s+(.*)");
    matches_t matches;
    match_pattern(str, pat, matches);
    size_t expected = 2;
    CHECK_EQUAL( expected, matches.size() );
    if (matches.size() == 2)  // test contents
    {
	 std::string expected_string("This is a test");
	 CHECK_EQUAL( expected_string, matches[1] );
    }
}

TEST(replace_pattern_test)
{
    std::string str("This is a test");
    std::string pat("This");
    std::string rep_str("That");
    std::string expected("That is a test");
    CHECK_EQUAL( expected, replace_pattern(str, pat, rep_str) );
}

TEST(trim_front_test)
{
    std::string actual("   This is a test");
    std::string expected("This is a test");
    CHECK_EQUAL( expected, trim_front(actual) );
}

TEST(trim_back_test)
{
     std::string actual("This is a test    ");
     std::string expected("This is a test");
     CHECK_EQUAL( expected, trim_back(actual) );
}

TEST(trim_test)
{
     std::string actual("       This is a test    ");
     std::string expected("This is a test");
     CHECK_EQUAL( expected, trim(actual) );
}

TEST(split_test)
{
    std::string str("This is a test");
    matches_t matches;
    split(str, matches);
    std::string expected("test");
    CHECK_EQUAL( expected, matches[3] );
}

TEST(split_sep_test)
{
    std::string str("http://www.google.com");
    std::string sep(":/");
    matches_t matches;
    split(str, sep, matches);
    std::string expected("www.google.com");
    CHECK_EQUAL( expected, matches[1] );
}
