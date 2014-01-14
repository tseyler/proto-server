/*
<boilerplate>



</boilerplate>
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
	virtual void run(void);

    protected:

	virtual void start_accept(void) = 0;
/*	void handle_accept(roku_http_session* session,
	const boost::system::error_code& error); */

	boost::asio::io_service& io_service_; 
	tcp::acceptor acceptor_;

    };

}

#endif
