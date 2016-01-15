//
// Created by tseyler on 1/5/16.
//

#ifndef PROTO_NET_TYPES_HPP_
#define PROTO_NET_TYPES_HPP_

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

    // this is a tcp socket
    typedef boost::asio::ip::tcp::socket proto_net_tcp_socket;

    // this is a tcp endpoint
    typedef boost::asio::ip::tcp::endpoint proto_net_tcp_endpoint;

    // this is a tcp acceptor type
    typedef boost::asio::ip::tcp::acceptor proto_net_tcp_acceptor;

    // this is a tcp resolver type
    typedef boost::asio::ip::tcp::resolver proto_net_tcp_resolver;

    // this is resolver::query type
    typedef boost::asio::ip::tcp::resolver::query proto_net_tcp_query;

    // this is a resolver::iterator type
    typedef boost::asio::ip::tcp::resolver::iterator prot_net_tcp_iterator;
}


#endif //PROTO_NET_TYPES_HPP
