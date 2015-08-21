

#include <core/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    proto_tcp_server::proto_tcp_server() : proto_server()
    {
        endpoint_ = basic_endpoint<tcp>(ps_internet_protocol(), port_num_);
    }

    proto_tcp_server::proto_tcp_server(int protocol_family, unsigned short port_num) : proto_server(protocol_family,
                                                                                                    port_num)
    {
        endpoint_ = basic_endpoint<tcp>(ps_internet_protocol(), port_num_);
    }

    proto_tcp_server::proto_tcp_server(const proto_tcp_server& ps)
    {
        clone(ps);
    }

    proto_tcp_server& proto_tcp_server::clone(const proto_tcp_server& ps)
    {
        proto_server::clone(dynamic_cast<const proto_server&>(ps));
        endpoint_ = ps_endpoint();

        return *this;
    }

    proto_tcp_server& proto_tcp_server::operator =(const proto_tcp_server& ps)
    {
        return clone(ps);
    }

    tcp proto_tcp_server::ps_internet_protocol(void) const
    {
        tcp ret(tcp::v4());

        switch (af_protocol_family_)
        {
            case PS_AF_INET: ret = tcp::v4(); break;
            case PS_AF_INET6: ret = tcp::v6(); break;
        }

        return ret;
    }

}
