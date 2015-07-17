/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef HTTP_MESSAGE_HPP_
#define HTTP_MESSAGE_HPP_

#include <net_data.hpp>
#include <http/http_headers.hpp>

namespace proto_http
{
    /*
      Compliant with rfc2616
      See: http://tools.ietf.org/html/rfc2626
    */

    class http_message
    {
    public:

	http_message();
	virtual void clone(const http_message& copy);

	virtual std::string http_version(void) const;
	virtual void http_version(const std::string& version);
	virtual http_headers headers(void) const;
	virtual http_headers& get_headers(void);
	virtual std::string header_to_string(void) const;
	virtual net_data body(void) const;
	virtual net_data& get_body(void);
	virtual std::string to_string(void) const;
	virtual net_data to_net_data(void) const;

    protected:

	std::string http_version_;
	http_headers headers_;
	net_data message_body_;
    };

}

#endif

