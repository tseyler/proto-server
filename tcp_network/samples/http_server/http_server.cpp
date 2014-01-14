/*
<boilerplate>



</boilerplate>
*/

#include <boost/bind.hpp>
#include <sstream>
#include <http/http_request_parser.hpp>
#include <http/http_response_parser.hpp>
#include <http/http_request_handler.hpp>
#include "http_server.hpp"

using namespace proto_http;


http_impl::http_server::http_server(boost::asio::io_service& io_service, 
			       short port) : tcp_net::tcp_server(io_service,
								 port)
{
    start_accept();
}

void 
http_impl::http_server::pipe(const net_data& req_data,
			     net_data& res_data)
{
    http_request_parser parser;
    http_request_message request_message;
    http_response_message response_message; 
    int status_code = HTTP_PARSE_SUCCEEDED( parser.protocol_parse(req_data, request_message) ) ? 200 : 400;
    http_request_handler handler(status_code);
    handler.handle_request(request_message, response_message);

    res_data = response_message.to_net_data();
}

void 
http_impl::http_server::start_accept(void)
{
    http_session* new_session = new http_session(io_service_, this);
    acceptor_.async_accept(dynamic_cast<tcp_net::tcp_session*>(new_session)->socket(), 
			   boost::bind(&http_server::handle_accept,
				       this,
				       new_session,
				       boost::asio::placeholders::error));
}

void 
http_impl::http_server::handle_accept(http_session* session,
				      const boost::system::error_code& error)
{
    if (!error)
    {
	session->start();
    }
    else
    {
	delete session;
    }

    start_accept();
}

