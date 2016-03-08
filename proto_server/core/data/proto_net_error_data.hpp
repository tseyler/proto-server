
#ifndef PROTO_NET_ERROR_DATA_HPP_
#define PROTO_NET_ERROR_DATA_HPP_

//
//  proto_net_error_data.hpp -
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <map>
#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_error_data : public proto_net_data
        {
        public:

            static proto_net_error_code_map error_code_map_;
            static void create_error_code_map(void);

            proto_net_error_data(proto_net_data_error_code ec = ec_success);
            proto_net_error_data(const std::string& ec_message, proto_net_data_error_code ec = ec_success);
            virtual ~proto_net_error_data();

            // getters
            proto_net_data_error_code ps_data_error_code(void) const { return ec_; }
            std::string ps_data_error_message(void) const { return error_message_; }
            // setters
            virtual void ps_data_error_code(proto_net_data_error_code ec) { ec_ = ec; }
            virtual void ps_data_error_message(const std::string& message) { error_message_ = message; }

        protected:

            proto_net_data_error_code ec_;
            std::string error_message_;
        };
    }
}



#endif //PROTO_SERVER_PROTO_NET_ERROR_DATA_HPP_
