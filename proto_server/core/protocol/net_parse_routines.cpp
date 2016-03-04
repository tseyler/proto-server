/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/


#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <core/protocol/net_parse_routines.hpp>

namespace proto_net
{
    namespace protocol
    {
        bool
        search_pattern(const std::string& str,
                       const std::string& pat)
        {
            boost::regex exp(pat);
            boost::smatch match;

            return boost::regex_search(str, match, exp);
        }

        bool
        search_pattern(const std::string& str,
                       const std::string& pat,
                       size_t& count)
        {
            boost::regex exp(pat);

            boost::sregex_token_iterator itr(str.begin(), str.end(), exp, 0);
            boost::sregex_token_iterator end;

            count = 0;
            for (; itr != end; ++itr)
                count++;

            return count;
        }

        bool
        search_pattern(const std::string& str,
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
        match_pattern(const std::string& str,
                      const std::string& pat)
        {
            boost::regex exp(pat);
            boost::smatch match;

            return boost::regex_match(str, match, exp);
        }

        bool
        match_pattern(const std::string& str,
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
        replace_pattern(const std::string& str,
                        const std::string& pat,
                        const std::string& rep_str)
        {
            boost::regex exp(pat);

            return boost::regex_replace(str, exp, rep_str);
        }

        std::string
        trim_front(const std::string& str)
        {
            return replace_pattern(str, "^\\s+", "");
        }

        std::string
        trim_back(const std::string& str)
        {
            return replace_pattern(str, "\\s+$", "");
        }

        std::string
        trim(const std::string& str)
        {
            return trim_back(trim_front(str));
        }

        void
        split(const std::string& str, matches_t& matches)
        {
            boost::tokenizer<> tok(str);
            for (boost::tokenizer<>::iterator it = tok.begin(); it != tok.end(); ++it)
                matches.push_back(*it);
        }

        void
        split(const std::string& str, const std::string& sep, matches_t& matches)
        {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
            boost::char_separator<char> s(sep.c_str());
            tokenizer tok(str, s);
            for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
                matches.push_back(*it);
        }
    }
}

