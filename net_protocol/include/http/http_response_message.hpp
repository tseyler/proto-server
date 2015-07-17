/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef HTTP_RESPONSE_MESSAGE_HPP_
#define HTTP_RESPONSE_MESSAGE_HPP_

#include <http/http_message.hpp>
#include <http/http_status_code.hpp>

namespace proto_http
{
    /*
      Compliant with rfc2616
      See: http://tools.ietf.org/html/rfc2626
    */

    class http_response_message : public http_message
    {
    public:

	http_response_message();
	http_response_message(const http_status_code& status_code);
	http_response_message(const http_response_message& copy);
	http_response_message& operator = (const http_response_message& rhs);
	virtual void clone(const http_response_message& copy);

	http_status_code status_code(void) const;
	http_status_code& get_status_code(void);

	// http_message
	virtual std::string http_version(void) const;
	virtual void http_version(const std::string& version);
	virtual http_headers headers(void) const;
	virtual http_headers& get_headers(void);
	virtual std::string status_line(void) const;
	virtual std::string header_to_string(void) const;
	virtual std::string to_string(void) const;
	virtual net_data body(void) const;
	virtual net_data& get_body(void);
	virtual net_data to_net_data(void) const;
	
    private:

	http_status_code status_code_;
    };

}

#endif
