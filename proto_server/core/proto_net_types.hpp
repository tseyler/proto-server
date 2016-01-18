//
// Created by tseyler on 1/5/16.
//

#ifndef PROTO_NET_TYPES_HPP__
#define PROTO_NET_TYPES_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

namespace proto_net
{
    // this is our service type
    typedef boost::asio::io_service proto_net_service;

    // this the service type as a shared pointer
    typedef boost::shared_ptr<proto_net_service> proto_net_service_ptr;

    // returns a reference from the shared ptr
    proto_net_service& proto_net_service_ref(proto_net_service_ptr ptr);

    // this is a tcp acceptor type
    typedef boost::asio::ip::tcp::acceptor proto_net_tcp_acceptor;
}


#endif //PROTO_NET_TYPES_HPP
