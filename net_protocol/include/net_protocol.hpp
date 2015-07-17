/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef NET_PROTOCOL_HPP_
#define NET_PROTOCOL_HPP_

#include <net_data.hpp>

namespace net_proto
{
    template <typename P, typename R>
    class net_protocol
    {
    public:

	// this parses a well-formed message.  Returns a result
	virtual R protocol_parse(const net_data& formed, P& parsed) = 0;
	// this forms a well-formed message.  Returns a result
	virtual R protocol_form(const P& parsed, net_data& formed) = 0;
    };

}

#endif

