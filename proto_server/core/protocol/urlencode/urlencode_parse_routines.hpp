//
// Created by tseyler on 3/8/16.
//

#ifndef URLENCODE_PARSE_ROUTINES_HPP_
#define URLENCODE_PARSE_ROUTINES_HPP_

#include <string>
#include <map>
#include <core/protocol/net_parse_routines.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace urlencode
        {
            typedef std::map<std::string, std::string> urlencode_key_values;
            typedef urlencode_key_values::iterator urlencode_key_values_iterator;
            typedef std::pair<std::string, std::string> urlencode_key_value_pair;

            // tokenize routines
            size_t tokenize_urlencode_line(const std::string line, matches_t& tokens);

            size_t tokenize_urlencode_key_value(matches_t& tokens, urlencode_key_values& key_values);

            std::string ue_encode(const std::string& str_in);
            std::string ue_decode(const std::string& str_in);
        }
    }
}
#endif //URLENCODE_PARSE_ROUTINES_HPP_
