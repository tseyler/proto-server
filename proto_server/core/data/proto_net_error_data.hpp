//
// Created by tseyler on 3/2/16.
//

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

#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        class proto_net_error_data : public proto_net_data
        {
        public:

            proto_net_error_data(proto_net_data_error_code ec = ec_success);
            virtual ~proto_net_error_data();

        protected:

            proto_net_data_error_code ec_;

        };
    }
}



#endif //PROTO_SERVER_PROTO_NET_ERROR_DATA_HPP_
