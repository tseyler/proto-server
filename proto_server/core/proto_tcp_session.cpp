

#include <core/proto_tcp_session.hpp>

using namespace boost::asio::ip;

namespace proto_net
{

    proto_tcp_session::proto_tcp_session(proto_tcp_server::Proto_TCP_IO_Object& tcp_io_object) :
            socket_(tcp_io_object->ps_io_service())
    {

    }

    proto_tcp_session::~proto_tcp_session()
    {

    }
}