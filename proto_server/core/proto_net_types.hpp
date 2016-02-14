//
// Created by tseyler on 1/5/16.
//

#ifndef PROTO_NET_TYPES_HPP_
#define PROTO_NET_TYPES_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#define THROW_BOOST_ERROR( e ) if (e.value() > 0) throw e

namespace proto_net
{
    // this is our service type
    typedef boost::asio::io_service proto_net_service;

    // this the service type as a shared pointer
    typedef boost::shared_ptr<proto_net_service> proto_net_service_ptr;

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
    typedef boost::asio::ip::tcp::resolver::iterator proto_net_tcp_iterator;

    typedef boost::system::error_code proto_net_error_code;

    typedef boost::scoped_ptr<boost::thread> proto_net_thread_ptr;


    // returns a reference from the shared ptr
    proto_net_service& proto_net_service_ref(proto_net_service_ptr ptr);

    // returns an iterator or throws a boost error
    proto_net_tcp_iterator ps_tcp_resolve(proto_net_tcp_resolver& resolver,
                                           proto_net_tcp_query& query) throw(proto_net_error_code);

    // performs a tcp connection given a socket and an iterator
    void ps_tcp_connect(proto_net_tcp_socket& socket,
                        proto_net_tcp_iterator& iterator) throw(proto_net_error_code);

    // this get an iterator that can be used to get the local IP(s)
    proto_net_tcp_iterator ps_tcp_local_ip(proto_net_tcp_resolver& resolver) throw(proto_net_error_code);


}


#endif //PROTO_NET_TYPES_HPP
