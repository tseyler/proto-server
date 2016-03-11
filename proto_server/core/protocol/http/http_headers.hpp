/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef HTTP_HEADERS_HPP_
#define HTTP_HEADERS_HPP_

#include <map>
#include <string>
#include <core/protocol/http/http_header_fields.hpp>

namespace proto_net
{
	namespace protocol
	{
		namespace http
		{
			typedef std::map<std::string, http_header_fields> http_headers_map;
			typedef http_headers_map::iterator http_headers_map_iterator;
			typedef http_headers_map::const_iterator http_headers_map_const_iterator;
			typedef std::pair<std::string, http_header_fields> http_headers_name_value;

			class http_headers
			{
			public:

				static const std::string entity_category;
				static const std::string general_category;
				static const std::string request_category;
				static const std::string response_category;

				http_headers()
				{ }

				http_headers(const http_headers &copy);

				http_headers &operator=(const http_headers &rhs);

				virtual void clone(const http_headers &copy);

				http_headers_map headers(void) const
				{ return headers_; }

				void add_http_headers(const std::string &category, const http_header_fields &fields);

				void remove_http_headers(const std::string &category);

				http_header_fields get_header_fields(const std::string &category);

				http_header_fields operator[](const std::string &category);

				http_headers_map headers_map(void)
				{ return headers_; }

				http_headers_map &get_headers_map(void)
				{ return headers_; }

				size_t size(void)
				{ return headers_.size(); }

				void clear(void)
				{ headers_.clear(); }

				std::string to_string(void) const;

			protected:

				http_headers_map headers_;
			};
		}
	}
}

#endif
