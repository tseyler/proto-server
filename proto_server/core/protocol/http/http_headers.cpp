/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <core/protocol/http/http_headers.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace http
        {
            const std::string http_headers::entity_category = "entity";
            const std::string http_headers::general_category = "general";
            const std::string http_headers::request_category = "request";
            const std::string http_headers::response_category = "response";

            http_headers::http_headers(const http_headers &copy)
            {
                clone(copy);
            }

            http_headers &
            http_headers::operator=(const http_headers &rhs)
            {
                clone(rhs);

                return *this;
            }

            void
            http_headers::clone(const http_headers &copy)
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
            http_headers::add_http_headers(const std::string &category, const http_header_fields &fields)
            {
                remove_http_headers(category);

                headers_.insert(http_headers_name_value(category, fields));
            }

            void
            http_headers::remove_http_headers(const std::string &category)
            {
                if (headers_.find(category) != headers_.end())
                    headers_.erase(category);
            }

            http_header_fields
            http_headers::get_header_fields(const std::string &category)
            {
                http_header_fields fields;

                if (headers_.find(category) != headers_.end())
                    fields = headers_[category];

                return fields;
            }

            http_header_fields
            http_headers::operator[](const std::string &category)
            {
                return get_header_fields(category);
            }

            std::string
            http_headers::to_string(void) const
            {
                std::stringstream ss;
                std::string req_headers;
                std::string res_headers;
                std::string gen_headers;
                std::string entity_headers;

                for (http_headers_map_const_iterator it = headers_.begin(); it != headers_.end(); it++)
                {
                    std::string category = (*it).first;
                    http_header_fields fields = (*it).second;
                    if (boost::iequals(category, "request"))
                        req_headers = fields.to_string();
                    else if (boost::iequals(category, "response"))
                        res_headers = fields.to_string();
                    else if (boost::iequals(category, "general"))
                        gen_headers = fields.to_string();
                    else if (boost::iequals(category, "entity"))
                        entity_headers = fields.to_string();
                    else
                        ss << fields.to_string();
                }
                ss << gen_headers << req_headers << res_headers << entity_headers;

                return ss.str();
            }
        }
    }
}
