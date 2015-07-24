/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace tcp_net
{
    class tcp_server
    {
    public:
	
		tcp_server(boost::asio::io_service& io_service, short port);
		virtual ~tcp_server() {}
		virtual void run(void);

    protected:

		virtual void start_accept(void) = 0;

		boost::asio::io_service& io_service_; 
		tcp::acceptor acceptor_;
    };
}

#endif
