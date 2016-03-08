

#ifndef PROTO_NET_STRING_DATA_HPP_
#define PROTO_NET_STRING_DATA_HPP_

//
//  proto_net_string_data.hpp -
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_string_data : public proto_net_data
        {
        public:

            proto_net_string_data();

            proto_net_string_data(const char* data);

            proto_net_string_data(const std::string& data);

            // copy constructor
            proto_net_string_data(const proto_net_string_data &copy_data);
            // converts to a string data
            proto_net_string_data(const proto_net_data &copy_data);

            virtual ~proto_net_string_data()
            {}

            virtual proto_net_string_data &operator = (const proto_net_string_data &rhs);

            virtual proto_net_string_data &operator+=(const proto_net_string_data &rhs);

            virtual proto_net_string_data operator+(const proto_net_string_data &rhs);

            virtual bool operator==(const proto_net_string_data &rhs) const;

            virtual bool operator!=(const proto_net_string_data &rhs) const;

            virtual void clone(const proto_net_string_data &copy_data);

            virtual void append(const proto_net_string_data& append_data);

            size_t length(void);
        };
    }
}


#endif //PROTO_NET_STRING_DATA_HPP_
