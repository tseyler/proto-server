//
// Created by tseyler on 3/9/16.
//

#include <boost/algorithm/string.hpp>
#include <core/protocol/urlencode/urlencode_parse_routines.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace urlencode
        {
            urlencode_key_values decode_map = {
                    {"%20", " "},
                    {"%21", "!"},
                    {"%22", "\""},
                    {"%23", "#"},
                    {"%24", "$"},
                 //   {"%25", "%"},
                    {"%26", "&"},
                    {"%27", "'"},
                    {"%28", "("},
                    {"%29", ")"},
                    {"%2A", "*"},
                    {"%2B", "+"},
                   // {"%2C", ","},
                    {"%3A", ":"},
            };


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
                        std::string k = ue_decode(tokens[0]);
                        std::string v = ue_decode(tokens[1]);
                        key_values.insert(urlencode_key_value_pair(k, v));
                        count++;
                    }
                }

                return count;
            }

            std::string
            ue_encode(const std::string& str_in)
            {
                std::string encoded(str_in);

                urlencode_key_values_iterator it = decode_map.begin();
                while (it != decode_map.end())
                {
                    urlencode_key_value_pair decode_pair = *it++;
                    encoded = boost::replace_all_copy(encoded, decode_pair.second, decode_pair.first);
                }

                return encoded;
            }

            std::string
            ue_decode(const std::string& str_in)
            {
                std::string decoded(str_in);

                urlencode_key_values_iterator it = decode_map.begin();
                while (it != decode_map.end())
                {
                    urlencode_key_value_pair decode_pair = *it++;
                    decoded = boost::replace_all_copy(decoded, decode_pair.first, decode_pair.second);
                }

                return decoded;
            }
        }
    }
}
