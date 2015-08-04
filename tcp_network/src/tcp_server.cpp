/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <boost/bind.hpp>
#include "tcp_net/tcp_server.hpp"

using namespace tcp_net;

tcp_net::tcp_server::tcp_server(boost::asio::io_service& io_service, short port) : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
{ }

void 
tcp_net::tcp_server::run(void) 
{ 
    io_service_.run(); 
} 
