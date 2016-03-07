/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef HTTP_REQUEST_MESSAGE_HPP_
#define HTTP_REQUEST_MESSAGE_HPP_

#include <core/protocol/http/http_message.hpp>

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

			class http_request_message : public http_message
			{
			public:

				http_request_message();

				http_request_message(const std::string &method, const std::string &uri);

				http_request_message(const http_request_message &copy);

				http_request_message &operator=(const http_request_message &rhs);

				virtual ~http_request_message()
				{}

				virtual void clone(const http_request_message &copy);

				// 5.1.1 Method
				std::string method(void) const;

				void method(const std::string &m);

				// 5.1.2 Request-URI
				std::string request_uri(void) const;

				void request_uri(const std::string &uri);

				// 5.1 Request-Line
				std::string request_line(void) const;

				// http_message
				virtual std::string http_version(void) const;

				virtual void http_version(const std::string &version);

				virtual http_headers headers(void) const;

				virtual http_headers &get_headers(void);

				virtual std::string header_to_string(void) const;

			private:

				std::string method_;
				std::string request_uri_;
			};
		}
	}
}

#endif
