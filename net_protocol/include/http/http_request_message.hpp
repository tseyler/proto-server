/*
<boilerplate>



</boilerplate>
*/

#ifndef HTTP_REQUEST_MESSAGE_HPP_
#define HTTP_REQUEST_MESSAGE_HPP_

#include <http/http_message.hpp>

namespace proto_http
{
    /*
      Compliant with rfc2616
      See: http://tools.ietf.org/html/rfc2626
    */

    class http_request_message : public http_message
    {
    public:

	http_request_message();
	http_request_message(const std::string& method,
			     const std::string& uri);
	http_request_message(const http_request_message& copy);
	http_request_message& operator = (const http_request_message& rhs);

	virtual void clone(const http_request_message& copy);

	// 5.1.1 Method
	std::string method(void) const;
	void method(const std::string& m);
	// 5.1.2 Request-URI
	std::string request_uri(void) const;
	void request_uri(const std::string& uri);
	// 5.1 Request-Line
	std::string request_line(void) const;

	// http_message
	virtual std::string http_version(void) const;
	virtual void http_version(const std::string& version);
	virtual http_headers headers(void) const;
	virtual http_headers& get_headers(void);
	virtual std::string header_to_string(void) const;
	virtual net_data body(void) const;
	virtual net_data& get_body(void);
	virtual std::string to_string(void) const;
	virtual net_data to_net_data(void) const;
	
    private:

	std::string method_;
	std::string request_uri_;
    };

}

#endif
