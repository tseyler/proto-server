

#include <core/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    tcp proto_tcp_server::ps_internet_protocol(int af_protocol_family)
    {
        tcp ret(tcp::v4());

        switch (af_protocol_family)
        {
            case PS_AF_INET: ret = tcp::v4(); break;
            case PS_AF_INET6: ret = tcp::v6(); break;
        }

        return ret;
    }

    proto_tcp_server::proto_tcp_server() : proto_server()
    {
        ps_initialize();
    }

    proto_tcp_server::proto_tcp_server(int protocol_family, unsigned short port_num) : proto_server(protocol_family,
                                                                                                    port_num)
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
        proto_server::clone(dynamic_cast<const proto_server&>(ps));

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
        io_object_  = Proto_TCP_IO_Object(new proto_io_object<tcp>(ps_internet_protocol(af_protocol_family_), port_num_));
    }

    void
    proto_tcp_server::ps_run(void)
    {
        io_object_->ps_io_service().run();
    }

    void
    proto_tcp_server::ps_start_accept(void)
    {

    }


}
