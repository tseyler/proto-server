/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <boost/bind.hpp>
#include "echo_server.hpp"

using namespace echo;

echo::echo_server::echo_server(boost::asio::io_service& io_service, short port) : tcp_net::tcp_server(io_service, port)
{
    start_accept();
}

void 
echo::echo_server::pipe(const net_data& req_data, net_data& res_data)
{
    res_data = req_data; // here is how we echo
}

void 
echo::echo_server::start_accept(void)
{
    echo_session* new_session = new echo_session(io_service_, this);
    acceptor_.async_accept(dynamic_cast<tcp_net::tcp_session*>(new_session)->socket(), 
			   boost::bind(&echo_server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

void 
echo::echo_server::handle_accept(echo_session* session,
				 const boost::system::error_code& error)
{
    if (!error)
		session->start();
    else
		delete session;

    start_accept();
}

