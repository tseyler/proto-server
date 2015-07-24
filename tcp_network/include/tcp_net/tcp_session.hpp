/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef TCP_SESSION_HPP_
#define TCP_SESSION_HPP_

#include <boost/asio.hpp>
#include <tcp_net/tcp_server_pipe.hpp>

using boost::asio::ip::tcp;

namespace tcp_net
{

    class tcp_session
    {
    public:

		tcp_session(boost::asio::io_service& io_service, tcp_net::tcp_server_pipe* pipe) : socket_(io_service),
						      																pipe_(pipe)
	    { }
		tcp::socket& socket(void) { return socket_; }
		virtual void start(void) = 0;
		virtual void read(void) = 0;
		virtual void write(const char* data, size_t data_size) = 0;
		
    protected:

		virtual void handle_read(const boost::system::error_code& error, size_t bytes_transferred) = 0;
		virtual void handle_write(const boost::system::error_code& error) = 0;

		tcp::socket socket_;
		tcp_net::tcp_server_pipe* pipe_;
    };
}

#endif
