//
//  proto_session.hpp - base class for server sessions
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SESSION_HPP_
#define PROTO_SESSION_HPP_

#include <core/data/proto_net_pipeline.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_session
        {
        public:

            proto_session(size_t buffer_size = 4096);
            virtual ~proto_session();

            // getters
            const char* ps_buffer(void) const;
            size_t ps_buffer_size(void) const;

        protected:

            size_t buffer_size_;
            char* buffer_;

        };

    }
}

#endif //PROTO_SESSION_HPP_
