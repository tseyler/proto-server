

#include <core/proto_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    template <typename InternetProtocol>
    proto_server<InternetProtocol>::proto_server() : af_protocol_family_(PS_AF_INET),
                                                        port_num_(80)
    {}

    template <typename InternetProtocol>
    proto_server<InternetProtocol>::proto_server(int protocol_family, unsigned short port_num) :
                                                                                af_protocol_family_(protocol_family),
                                                                                port_num_(port_num)
    {}

    template <typename InternetProtocol>
    proto_server<InternetProtocol>::proto_server(const proto_server& ps)
    {
        clone(ps);
    }

    template <typename InternetProtocol>
    proto_server<InternetProtocol>& proto_server<InternetProtocol>::clone(const proto_server& ps)
    {
        af_protocol_family_ = ps.ps_af_protocol_family();
        port_num_ = ps.ps_port_number();

        return *this;
    }

    template <typename InternetProtocol>
    proto_server<InternetProtocol>& proto_server<InternetProtocol>::operator =(const proto_server& ps)
    {
        return clone(ps);
    }

    template <typename InternetProtocol>
    int proto_server<InternetProtocol>::ps_af_protocol_family(void) const
    {
        return af_protocol_family_;
    }

    template <typename InternetProtocol>
    unsigned short proto_server<InternetProtocol>::ps_port_number(void) const
    {
        return port_num_;
    }

    template <typename InternetProtocol>
    basic_endpoint<InternetProtocol> proto_server<InternetProtocol>::ps_endpoint(void) const
    {
        return endpoint_;
    }
}