/*
<boilerplate>



</boilerplate>
*/

#include <iostream>
#include <sstream>
#include <http/http_constants.hpp>
#include <http/http_request_message.hpp>


proto_http::http_request_message::http_request_message() : http_message(),
							   method_("GET"),
							   request_uri_("*")
{
    headers_.add_http_headers("request", http_header_fields());
    headers_.add_http_headers("general", http_header_fields());
    headers_.add_http_headers("entity", http_header_fields());
}

proto_http::http_request_message::http_request_message(const std::string& method,
						       const std::string& uri) : http_message(),
										 method_(method),
										 request_uri_(uri)
{
    headers_.add_http_headers("request", http_header_fields());
    headers_.add_http_headers("general", http_header_fields());
    headers_.add_http_headers("entity", http_header_fields());
}

proto_http::http_request_message::http_request_message(const http_request_message& copy)
{
    clone(copy);
}
	
proto_http::http_request_message& 
proto_http::http_request_message::operator = (const http_request_message& rhs)
{
    if (&rhs != this)
	clone(rhs);

    return *this;
}

void 
proto_http::http_request_message::clone(const http_request_message& copy)
{
    method_ = copy.method();
    request_uri_ = copy.request_uri();
    http_message::clone(copy);
}

std::string 
proto_http::http_request_message::method(void) const 
{ 
    return method_; 
}

void 
proto_http::http_request_message::method(const std::string& m) 
{ 
    method_ = m; 
}

std::string 
proto_http::http_request_message::request_uri(void) const 
{ 
    return request_uri_; 
}

void 
proto_http::http_request_message::request_uri(const std::string& uri) 
{ 
    request_uri_ = uri; 
}
	
std::string 
proto_http::http_request_message::request_line(void) const // 5.1 Request-Line
{
    std::stringstream ss;
    ss << method_ << sp << request_uri_ << sp << http_version_ << crlf;

    return ss.str();
}

std::string 
proto_http::http_request_message::http_version(void) const
{
    return http_message::http_version();
}

void 
proto_http::http_request_message::http_version(const std::string& version)
{
    http_message::http_version(version);
}
	
proto_http::http_headers 
proto_http::http_request_message::headers(void) const
{
    return http_message::headers();
}

proto_http::http_headers& 
proto_http::http_request_message::get_headers(void)
{
    return http_message::get_headers();
}

std::string 
proto_http::http_request_message::header_to_string(void) const
{
    std::stringstream ss;
    ss << request_line(); // request line
    ss << http_message::header_to_string();

    return ss.str();
}

net_data 
proto_http::http_request_message::body(void) const
{
    return http_message::body();
}

net_data& 
proto_http::http_request_message::get_body(void)
{
    return http_message::get_body();
}

std::string 
proto_http::http_request_message::to_string(void) const
{
    return http_message::to_string();
}

net_data 
proto_http::http_request_message::to_net_data(void) const
{
    return http_message::to_net_data();
}



