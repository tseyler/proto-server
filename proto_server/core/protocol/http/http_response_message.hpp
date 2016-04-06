//
//  http_response_message.hpp - class that represents an HTTP response message
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef HTTP_RESPONSE_MESSAGE_HPP_
#define HTTP_RESPONSE_MESSAGE_HPP_

#include <core/protocol/http/http_message.hpp>
#include <core/protocol/http/http_status_code.hpp>

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

			class http_response_message : public http_message
			{
			public:

				http_response_message();

				http_response_message(const http_status_code &status_code);

				http_response_message(const http_response_message &copy);

				http_response_message &operator=(const http_response_message &rhs);

				virtual void clone(const http_response_message &copy);

				http_status_code status_code(void) const;

				http_status_code &get_status_code(void);

				// http_message
				virtual std::string http_version(void) const;

				virtual void http_version(const std::string &version);

				virtual http_headers headers(void) const;

				virtual http_headers &get_headers(void);

				virtual std::string status_line(void) const;

				virtual std::string header_to_string(void) const;

			private:

				http_status_code status_code_;
			};
		}
	}
}

#endif
