

#include <core/server/proto_tcp_session.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {
        proto_tcp_session::proto_tcp_session(proto_io_tcp_object& tcp_io_object) : socket_(tcp_io_object.ps_io_service())
        {

        }

        proto_tcp_session::~proto_tcp_session()
        {

        }
    }

}