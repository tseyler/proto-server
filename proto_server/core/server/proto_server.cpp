

#include <core/server/proto_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {

//        proto_server::proto_server() : port_num_(80), af_protocol_family_(PS_AF_INET)
//        {}
//
//        proto_server::proto_server(unsigned short port_num, int protocol_family /*= PS_AF_INET*/) :
//                port_num_(port_num),
//                af_protocol_family_(protocol_family)
//        {}


//        proto_server::proto_server(const proto_server& ps)
//        {
//            clone(ps);
//        }


//        proto_server&
//        proto_server::clone(const proto_server& ps)
//        {
//            af_protocol_family_ = ps.ps_af_protocol_family();
//            port_num_ = ps.ps_port_number();
//
//            return *this;
//        }


//        proto_server&
//        proto_server::operator =(const proto_server& ps)
//        {
//            return clone(ps);
//        }

//    typename proto_server<InternetProtocol>::Proto_IO_Object&
//    proto_server<InternetProtocol>::ps_io_object(void) const
//    {
//        return io_object_;
//    }


//        int
//        proto_server::ps_af_protocol_family(void) const
//        {
//            return af_protocol_family_;
//        }

//        unsigned short
//        proto_server::ps_port_number(void) const
//        {
//            return port_num_;
//        }
    }

}