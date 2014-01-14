/*
<boilerplate>



</boilerplate>
*/

#ifndef CONTROL4_SESSION_HPP_
#define CONTROL4_SESSION_HPP_

#include <boost/asio.hpp>
#include <tcp_net/tcp_session.hpp>

namespace control4
{

    class control4_session : public tcp_net::tcp_session
    {
    public:

	control4_session(boost::asio::io_service& io_service,
		     tcp_net::tcp_server_pipe* pipe);
	virtual void start(void);
	virtual void read(void);
	virtual void write(const char* data, 
			   size_t data_size);

    protected:

	virtual void handle_read(const boost::system::error_code& error,
				 size_t bytes_transferred);
	virtual void handle_write(const boost::system::error_code& error);

    private:

	enum {max_length = 4096};
	char data_[max_length];
    };

}

#endif
