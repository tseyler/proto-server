/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <boost/bind.hpp>
#include "http_session.hpp"

http_impl::http_session::http_session(boost::asio::io_service& io_service,
				 tcp_net::tcp_server_pipe* pipe) : 
    tcp_net::tcp_session(io_service, pipe)
{ }

void
http_impl::http_session::start(void)
{
    read();
}

void 
http_impl::http_session::read(void)
{
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
			    boost::bind(&http_session::handle_read,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}
	
void 
http_impl::http_session::write(const char* data, size_t data_size)
{
    boost::asio::async_write(socket_,
			     boost::asio::buffer(data, data_size),
			     boost::bind(&http_session::handle_write,
					 this,
					 boost::asio::placeholders::error));
}

void 
http_impl::http_session::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
		// handle a read here
		if (pipe_)
		{
			net_data req_data(data_, bytes_transferred);
			net_data res_data;
			pipe_->pipe(req_data, res_data); // all of the magic takes place inside the pipe
			write(res_data.data(), res_data.data_size());
		}
    }
    else
    	delete this;
}

void 
http_impl::http_session::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
		// handle a post write here
		read(); // just go back to reading
    }
    else
    	delete this;
}



