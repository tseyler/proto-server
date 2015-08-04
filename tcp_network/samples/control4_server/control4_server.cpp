/*
<boilerplate>



</boilerplate>
*/

#include <iostream>

#include <boost/bind.hpp>
#include "control4_server.hpp"

using namespace control4;

control4::control4_server::control4_server(boost::asio::io_service& io_service, 
			       short port) : tcp_net::tcp_server(io_service,
								 port)
{
    start_accept();
}

void 
control4::control4_server::pipe(const net_data& req_data,
			net_data& res_data)
{
    res_data = req_data; // here is how we control4

    std::cout << res_data.to_string() << std::endl;
    net_data xml_data(res_data);
    xml_data.data_type(data_text);
    std::cout << xml_data.to_string() << std::endl;
}

void 
control4::control4_server::start_accept(void)
{
    control4_session* new_session = new control4_session(io_service_, this);
    acceptor_.async_accept(dynamic_cast<tcp_net::tcp_session*>(new_session)->socket(), 
			   boost::bind(&control4_server::handle_accept,
				       this,
				       new_session,
				       boost::asio::placeholders::error));
}

void 
control4::control4_server::handle_accept(control4_session* session,
				 const boost::system::error_code& error)
{
    if (!error)
    	session->start();
    else
    	delete session;

    start_accept();
}

