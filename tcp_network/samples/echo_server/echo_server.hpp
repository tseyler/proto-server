/*
<boilerplate>



</boilerplate>
*/

#ifndef ECHO_SERVER_HPP_
#define ECHO_SERVER_HPP_

#include <boost/asio.hpp>
#include <tcp_net/tcp_server.hpp>
#include <tcp_net/tcp_server_pipe.hpp>
#include <net_data.hpp>
#include "echo_session.hpp"

using boost::asio::ip::tcp;

namespace echo
{

    class echo_server : public tcp_net::tcp_server,
			public tcp_net::tcp_server_pipe
    {
    public:

	echo_server(boost::asio::io_service& io_service, short port);

	virtual void pipe(const net_data& req_data, // the request data
			  net_data& res_data);  // the response data

    protected:

	virtual void start_accept(void);
	virtual void handle_accept(echo_session* session,
				   const boost::system::error_code& error);
    };

}

#endif

