//
// Created by tseyler on 1/5/16.
//

#include <core/proto_net_types.hpp>

namespace proto_net
{

    proto_net_service&
    proto_net_service_ref(proto_net_service_ptr ptr)
    {
        return *ptr.get();
    }

    proto_net_tcp_iterator
    ps_tcp_resolve(proto_net_tcp_resolver& resolver, proto_net_tcp_query& query) throw(proto_net_error_code)
    {
        proto_net_error_code ec;

        return resolver.resolve(query, ec);
    }

    void
    ps_tcp_connect(proto_net_tcp_socket& socket, proto_net_tcp_iterator& iterator) throw(proto_net_error_code)
    {
        proto_net_error_code ec;

        proto_net_tcp_endpoint ep = *iterator;
        socket.connect(ep, ec);
    }

    proto_net_tcp_iterator
    ps_tcp_local_ip(proto_net_tcp_resolver& resolver) throw(proto_net_error_code)
    {
        proto_net_error_code ec;
        proto_net_tcp_query query(boost::asio::ip::host_name(ec));

        return ps_tcp_resolve(resolver, query);
    }
}
