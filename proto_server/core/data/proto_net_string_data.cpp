//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <boost/algorithm/string.hpp>
#include <core/data/proto_net_string_data.hpp>


namespace proto_net
{
    namespace data
    {
        proto_net_string_data::proto_net_string_data() : proto_net_data(data_text)
        { }

        proto_net_string_data::proto_net_string_data(const char* data) : proto_net_data(data, strlen(data), data_text)
        { }

        proto_net_string_data::proto_net_string_data(const std::string& data) : proto_net_data(data)
        { }

        proto_net_string_data::proto_net_string_data(const proto_net_string_data& copy_data) :
                proto_net_data(copy_data)
        { }

        proto_net_string_data::proto_net_string_data(const proto_net_data &copy_data) :
                proto_net_data(copy_data.data(), strlen(copy_data.data()), data_text)
        { }

        proto_net_string_data&
        proto_net_string_data::operator = (const proto_net_string_data &rhs)
        {
            if (&rhs != this)
                clone(rhs);

            return *this;
        }

        proto_net_string_data&
        proto_net_string_data::operator += (const proto_net_string_data &rhs)
        {
            append(rhs);

            return *this;
        }

        proto_net_string_data
        proto_net_string_data::operator + (const proto_net_string_data &rhs)
        {
            proto_net_string_data result(to_string());
            result.append(rhs);

            return result;
        }

        bool
        proto_net_string_data::operator == (const proto_net_string_data &rhs) const
        {
            return (boost::equal(rhs.to_string(), to_string()));
        }

        bool
        proto_net_string_data::operator != (const proto_net_string_data &rhs) const
        {
            return !(boost::equal(rhs.to_string(), to_string()));
        }

        void
        proto_net_string_data::clone(const proto_net_string_data& copy_data)
        {
            proto_net_data::clone(copy_data);
        }

        void
        proto_net_string_data::append(const proto_net_string_data& append_data)
        {
            std::stringstream ss;
            ss << to_string() << append_data.to_string();
            proto_net_string_data appended_data(ss.str());
            clone(appended_data);
        }

        size_t
        proto_net_string_data::length(void)
        {
            return to_string().length();
        }
    }
}

