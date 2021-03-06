//
//  net_parse_routines.hpp - parse rountines
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef NET_PARSE_ROUTINES_HPP_
#define NET_PARSE_ROUTINES_HPP_


#include <string>
#include <vector>

namespace proto_net
{
    namespace protocol
    {
        typedef std::vector<std::string> matches_t;
        typedef matches_t::iterator matches_iterator;

        // search routines
        bool search_pattern(const std::string& str, const std::string& pat);
        bool search_pattern(const std::string& str, const std::string& pat, size_t& count);
        bool search_pattern(const std::string& str, const std::string& pat, matches_t& matches);

        // match routines
        bool match_pattern(const std::string& str, const std::string& pat);
        bool match_pattern(const std::string& str, const std::string& pat, matches_t& matches);

        // replace routines
        std::string replace_pattern(const std::string& str, const std::string& pat, const std::string& rep_str);

        // trim routines
        std::string trim_front(const std::string& str);
        std::string trim_back(const std::string& str);
        std::string trim(const std::string& str);

        // split routines
        void split(const std::string& str, matches_t& matches);
        void split(const std::string& str, const std::string& sep, matches_t& matches);
    }
}

#endif
