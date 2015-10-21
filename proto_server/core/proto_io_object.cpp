//
// Created by Terry Seyler on 8/21/15.
//

#include <core/proto_io_object.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    proto_io_object::proto_io_object(unsigned short port_num /*= 80*/) : port_num_(port_num)
    {

    }

    io_service&
    proto_io_object::ps_io_service(void)
    {
        return io_service_;
    }

    unsigned short
    proto_io_object::ps_io_port_num(void) const
    {
        return port_num_;
    }

}