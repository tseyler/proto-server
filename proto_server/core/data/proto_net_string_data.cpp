//
// Created by tseyler on 2/29/16.
//

#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>

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
    }
}

