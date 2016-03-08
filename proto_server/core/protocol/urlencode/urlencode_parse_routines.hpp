//
// Created by tseyler on 3/8/16.
//

#ifndef URLENCODE_PARSE_ROUTINES_HPP_
#define URLENCODE_PARSE_ROUTINES_HPP_

#include <string>
#include <vector>
#include <core/data/proto_net_string_data.hpp>
#include <core/protocol/net_parse_routines.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace urlencode
        {
            // tokenize routines
            size_t tokenize_line(const std::string line, matches_t &tokens);
        }
    }
}
#endif //URLENCODE_PARSE_ROUTINES_HPP_
