/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef TCP_SERVER_PIPE_HPP_
#define TCP_SERVER_PIPE_HPP_

#include <net_data.hpp>

namespace tcp_net
{

    class tcp_server_pipe
    {
    public:

		virtual void pipe(const net_data& req_data, // the request data
			  				net_data& res_data) = 0;  // the response data
    };
}

#endif
