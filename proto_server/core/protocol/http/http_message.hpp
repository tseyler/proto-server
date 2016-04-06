//
//  http_message.hpp - class that represents an HTTP message
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef HTTP_MESSAGE_HPP_
#define HTTP_MESSAGE_HPP_

#include <core/data/proto_net_string_data.hpp>
#include <core/protocol/http/http_headers.hpp>

namespace proto_net
{
	using namespace data;

	namespace protocol
	{
		namespace http
		{
			/*
			  Compliant with rfc2616
			  See: http://tools.ietf.org/html/rfc2626
			*/

			class http_message
			{
			public:

				http_message();

				void clone(const http_message &copy);

				virtual std::string http_version(void) const;

				virtual void http_version(const std::string &version);

				virtual http_headers headers(void) const;

				virtual http_headers &get_headers(void);

				virtual std::string header_to_string(void) const;

				virtual proto_net_string_data body(void) const;

				virtual void body(const proto_net_string_data& data);

				virtual std::string to_string(void) const;

				virtual proto_net_string_data to_net_data(void) const;

				virtual size_t content_length(void);

			protected:

				std::string http_version_;
				http_headers headers_;
				proto_net_string_data message_body_;
			};
		}
	}
}

#endif

