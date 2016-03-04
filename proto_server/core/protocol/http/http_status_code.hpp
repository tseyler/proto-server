/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef HTTP_STATUS_CODE_HPP_
#define HTTP_STATUS_CODE_HPP_

#include <string>

namespace proto_net
{
	namespace protocol
	{
		namespace http
		{
			/*
			  Compliant with rfc2616
			  See: http://tools.ietf.org/html/rfc2626
			*/

			typedef enum
			{
				code_class_bad,
				code_class_informational,
				code_class_success,
				code_class_redirection,
				code_class_client_error,
				code_class_server_error,
			} status_code_class;

			class http_status_code
			{
			public:

				http_status_code(int code = 400); // Bad Request 10.4.1
				http_status_code(const http_status_code &copy);

				virtual http_status_code &operator=(const http_status_code &rhs);

				virtual void clone(const http_status_code &copy);

				int status_code(void) const;

				void status_code(int code);

				status_code_class code_class(void) const;

				virtual std::string reason_phrase(void) const;

				virtual std::string to_string(void) const;

			private:

				int status_code_;
			};
		}
	}
}

#endif
