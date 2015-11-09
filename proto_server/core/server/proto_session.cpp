//
// Created by Terry Seyler on 10/27/15.
//

#include <core/server/proto_session.hpp>

using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        proto_session::proto_session(proto_net_io& ps_io, size_t buffer_size /* = 4096*/) : ps_io_(ps_io),
                                                                                            buffer_size_(buffer_size)
        {
            buffer_ = new char[buffer_size_];
        }

        proto_session::~proto_session()
        {
            delete [] buffer_;
        }


        const char*
        proto_session::ps_buffer(void) const
        {
            return buffer_;
        }

        size_t
        proto_session::ps_buffer_size(void) const
        {
            return buffer_size_;
        }

        proto_net_io&
        proto_session::ps_io(void)
        {
            return ps_io_;
        }

    }
}
