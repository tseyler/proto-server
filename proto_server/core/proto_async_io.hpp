//
// Created by tseyler on 2/12/16.
//

#ifndef PROTO_ASYNC_IO_HPP_
#define PROTO_ASYNC_IO_HPP_

#include <core/data/proto_net_data.hpp>


namespace proto_net
{
    using namespace proto_net::data;

    class proto_async_io
    {
    public:

        virtual void ps_async_read(void) = 0;
        virtual void ps_async_write(proto_net_out_data& data_out) = 0;
    };

}

#endif //PROTO_ASYNC_IO_HPP_

