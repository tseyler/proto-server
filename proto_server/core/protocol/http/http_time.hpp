//
//  http_time.hpp - class that represents an HTTP time
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016, 2017 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SERVER_HTTP_TIME_HPP_
#define PROTO_SERVER_HTTP_TIME_HPP_

#include <string>
#include <ctime>
#include <sstream>

#include <core/data/proto_net_string_data.hpp>

namespace proto_net
{
    using namespace data;

    namespace protocol
    {
        namespace http
        {
            class http_time
            {
            public:

                http_time();
                http_time(std::time_t t);
                http_time(const http_time& http_t);
                http_time& operator = (const http_time& http_t);

                virtual ~http_time();

                std::string to_string(void);
                proto_net_string_data to_string_data(void);

                std::time_t get_time(void) const;

            protected:

                std::time_t t_;
            };

        }
    }
}

#endif //PROTO_SERVER_HTTP_TIME_HPP_
