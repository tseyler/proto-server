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
        }
    }
}
