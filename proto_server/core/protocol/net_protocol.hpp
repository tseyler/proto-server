/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef NET_PROTOCOL_HPP_
#define NET_PROTOCOL_HPP_

#include <core/data/proto_net_string_data.hpp>

namespace proto_net
{
	using namespace data;

	namespace protocol
	{
		template <typename P, typename R>
		class net_protocol
		{
		public:

			// this parses a well-formed message.  Returns a result
			virtual R protocol_parse(const proto_net_string_data& formed, P& parsed) = 0;
			// this forms a well-formed message.  Returns a result
			virtual R protocol_form(const P& parsed, proto_net_string_data& formed) = 0;
		};
	}
}

#endif

