//
//  http_time.hpp - class that represents an HTTP time
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016, 2017 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/protocol/http/http_time.hpp>

namespace proto_net
{
    using namespace data;

    namespace protocol
    {
        namespace http
        {
            http_time::http_time() : t_(std::time(NULL))
            {}

            http_time::http_time(std::time_t t) : t_(t)
            {}

            http_time::http_time(const http_time& http_t)
            {
                t_ = http_t.get_time();
            }

            http_time&
            http_time::operator = (const http_time& http_t)
            {
                t_ = http_t.get_time();

                return *this;
            }

            http_time::~http_time()
            {}

            std::string
            http_time::to_string(void)
            {
                std::stringstream ss;

                char mb_str[128];
                if (std::strftime(mb_str, sizeof(mb_str), "%a, %d %b %Y %T  GMT", std::gmtime(&t_)))
                    ss << mb_str;

                return ss.str();
            }

            proto_net_string_data
            http_time::to_string_data(void)
            {
               return proto_net_string_data(to_string());
            }

            std::time_t
            http_time::get_time(void) const
            {
                return t_;
            }
        }
    }
}

