//
// Created by tseyler on 3/9/16.
//

#include <core/protocol/urlencode/urlencode_parse_routines.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace urlencode
        {
            // tokenize routines
            size_t
            tokenize_urlencode_line(const std::string line, matches_t &tokens)
            {
                std::string sep("&");
                split(line, sep, tokens);

                return tokens.size();
            }

            size_t
            tokenize_urlencode_key_value(matches_t& tokens, urlencode_key_values& key_values)
            {
                std::string sep("=");
                size_t count(0);

                matches_iterator mit = tokens.begin();
                while (mit != tokens.end())
                {
                    matches_t tokens;
                    std::string kv = *mit++;
                    split(kv, sep, tokens);
                    if (tokens.size() >= 2) // key=value = size 2
                    {
                        key_values.insert(urlencode_key_value_pair(tokens[0], tokens[1]));
                        count++;
                    }
                }

                return count;
            }
        }
    }
}
