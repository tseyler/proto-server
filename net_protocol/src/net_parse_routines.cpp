/*
  <boilerplate>



  </boilerplate>
*/


#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <net_parse_routines.hpp>


bool 
net_proto::search_pattern(const std::string& str, 
			  const std::string& pat)
{
    boost::regex exp(pat);
    boost::smatch match;

    return boost::regex_search(str, match, exp);
}

bool 
net_proto::search_pattern(const std::string& str, 
			  const std::string& pat, 
			  size_t& count)
{
    boost::regex exp(pat);

    boost::sregex_token_iterator itr(str.begin(), str.end(), exp, 0);
    boost::sregex_token_iterator end;

    count = 0;
    for (; itr != end; ++itr)
	count++;

    return (count);
}

bool 
net_proto::search_pattern(const std::string& str, 
			  const std::string& pat, 
			  matches_t& matches)
{
    bool found(false);
    
    boost::regex exp(pat);

    boost::sregex_token_iterator itr(str.begin(), str.end(), exp, 0);
    boost::sregex_token_iterator end;

    for (; itr != end; ++itr)
    {
	matches.push_back(std::string(itr->first, itr->second));
	found = true;
    }

    return found;
}

bool 
net_proto::match_pattern(const std::string& str, 
			 const std::string& pat)
{
    boost::regex exp(pat);
    boost::smatch match;

    return boost::regex_match(str, match, exp);
}

bool 
net_proto::match_pattern(const std::string& str, 
			 const std::string& pat, 
			 matches_t& matches)
{
   boost::regex exp(pat);
   boost::smatch match;

   bool matched = boost::regex_match(str, match, exp);
   if (matched)
   {
       for (size_t i = 0; i < match.size(); i++)
	   matches.push_back(match[i]);
   }

   return matched;
}

std::string
net_proto::replace_pattern(const std::string& str, 
			   const std::string& pat, 
			   const std::string& rep_str)
{
    boost::regex exp(pat);

    return boost::regex_replace(str, exp, rep_str);
}

std::string
net_proto::trim_front(const std::string& str)
{
    return replace_pattern(str, "^\\s+", "");
}
 
std::string
net_proto::trim_back(const std::string& str)
{
    return replace_pattern(str, "\\s+$", "");
}

std::string
net_proto::trim(const std::string& str)
{
   return trim_back(trim_front(str));
}

void 
net_proto::split(const std::string& str, matches_t& matches)
{
    boost::tokenizer<> tok(str);
    for (boost::tokenizer<>::iterator it = tok.begin(); it != tok.end(); ++it)
	matches.push_back(*it);
}

void 
net_proto::split(const std::string& str, const std::string& sep, matches_t& matches)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> s(sep.c_str());
    tokenizer tok(str, s);
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
	matches.push_back(*it);
}
