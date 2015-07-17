/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <http/http_headers.hpp>


proto_http::http_headers::http_headers(const http_headers& copy)
{
    clone(copy);
}

proto_http::http_headers& 
proto_http::http_headers::operator = (const http_headers& rhs)
{
    clone(rhs);

    return *this;
}

void 
proto_http::http_headers::clone(const http_headers& copy)
{
    headers_.clear();
    http_headers_map copy_headers = copy.headers();
    http_headers_map_const_iterator it = copy_headers.begin();
    while (it != copy_headers.end())
    {
	add_http_headers((*it).first, (*it).second);
	it++;
    }
}

void 
proto_http::http_headers::add_http_headers(const std::string& category, 
					   const http_header_fields& fields)
{
    remove_http_headers(category);

    headers_.insert(http_headers_name_value(category, fields));
}

void 
proto_http::http_headers::remove_http_headers(const std::string& category)
{
    if (headers_.find(category) != headers_.end())
	headers_.erase(category);
}

proto_http::http_header_fields
proto_http::http_headers::get_header_fields(const std::string& category)
{
    http_header_fields fields;

    if (headers_.find(category) != headers_.end())
	fields = headers_[category];

    return fields;
}

proto_http::http_header_fields 
proto_http::http_headers::operator [] (const std::string& category)
{
    return get_header_fields(category);
}

std::string 
proto_http::http_headers::to_string(void) const
{
    std::stringstream ss;
    std::string req_headers;
    std::string res_headers;
    std::string gen_headers;
    std::string entity_headers;

    for (http_headers_map_const_iterator it = headers_.begin();
	 it != headers_.end();
	 it++)
    {
	std::string category = (*it).first;
	http_header_fields fields = (*it).second;
	if (category == "request")
	    req_headers = fields.to_string();
	else if (category == "response")
	    res_headers = fields.to_string();
	else if (category == "general")
	    gen_headers = fields.to_string();
	else if (category == "entity")
	    entity_headers = fields.to_string();
	else
	    ss << fields.to_string();
    }
    ss << gen_headers << req_headers << res_headers << entity_headers;

    return ss.str();
}
