/*
<boilerplate>



</boilerplate>
*/

#include <iostream>
#include <sstream>
#include <http/http_constants.hpp>
#include <http/http_message.hpp>


proto_http::http_message::http_message() : http_version_("HTTP/1.1"),
					   headers_(),
					   message_body_()
{ }

void 
proto_http::http_message::clone(const http_message& copy)
{
    http_version_ = copy.http_version();
    headers_ = copy.headers(); // using http_headers assignment operator
    message_body_ = copy.body();
}

std::string 
proto_http::http_message::http_version(void) const 
{ 
    return http_version_; 
}

void 
proto_http::http_message::http_version(const std::string& version) 
{ 
    http_version_ = version; 
}

proto_http::http_headers 
proto_http::http_message::headers(void) const 
{ 
    return headers_; 
}

proto_http::http_headers& 
proto_http::http_message::get_headers(void) 
{ 
    return headers_; 
}

std::string 
proto_http::http_message::header_to_string(void) const
{
    std::stringstream ss;

    ss << headers_.to_string();
    ss << crlf; // end of header

    return ss.str();
}

std::string 
proto_http::http_message::to_string(void) const
{
    std::stringstream ss;
    ss << header_to_string() << message_body_.to_string();

    return ss.str();
}

net_data 
proto_http::http_message::body(void) const 
{ 
    return message_body_; 
}

net_data& 
proto_http::http_message::get_body(void) 
{ 
    return message_body_; 
}

net_data 
proto_http::http_message::to_net_data(void) const
{
    std::string header = header_to_string();
    net_data header_data(header);

    return header_data + message_body_;
}

