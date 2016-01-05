//
// Created by Terry Seyler on 10/27/15.
//

#ifndef PROTO_SESSION_HPP__
#define PROTO_SESSION_HPP__

#include <core/data/proto_net_io.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_session
        {
        public:

            proto_session(proto_net_io& ps_io, size_t buffer_size = 4096);
            virtual ~proto_session();

            virtual void start(void) = 0;
            virtual void read(void) = 0;
            virtual void write(const char* data, size_t data_size) = 0;

            // getters
            const char* ps_buffer(void) const;
            size_t ps_buffer_size(void) const;
            proto_net_io& ps_io(void);

        protected:

            proto_net_io& ps_io_;
            size_t buffer_size_;
            char* buffer_;

        };
    }
}

#endif //PROTO_SESSION_HPP__
