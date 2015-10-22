

#include <core/server/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {


//        proto_tcp_server::proto_tcp_server() : proto_server()
//        {
//            ps_initialize();
//        }

        proto_tcp_server::proto_tcp_server(unsigned short port_num /* = 80*/) : proto_server()
        {
            ps_initialize();
        }

        proto_tcp_server::proto_tcp_server(const proto_tcp_server& ps)
        {
            clone(ps);
        }

        proto_tcp_server&
        proto_tcp_server::clone(const proto_tcp_server& ps)
        {
          //  proto_server::clone(dynamic_cast<const proto_server&>(ps));

            return *this;
        }

        proto_tcp_server&
        proto_tcp_server::operator =(const proto_tcp_server& ps)
        {
            return clone(ps);
        }

        void
        proto_tcp_server::ps_initialize(void)
        {
            io_object_  = //Proto_TCP_IO_Object(new proto_io_object<tcp>(ps_internet_protocol(af_protocol_family_), port_num_));
        }

        void
        proto_tcp_server::ps_run(void)
        {
            //  io_object_->ps_io_service().run();
        }

        void
        proto_tcp_server::ps_start_accept(void)
        {

        }
    }



}
