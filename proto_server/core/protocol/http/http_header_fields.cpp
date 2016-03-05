/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <core/protocol/http/http_constants.hpp>
#include <core/protocol/http/http_header_fields.hpp>

namespace proto_net
{
    namespace protocol
    {
        namespace http
        {
            void
            http_header_fields::insert_header_field(header_fields &fields, const std::string &name, const std::string &value)
            {
                if (fields.find(name) == fields.end())
                    fields.insert(header_name_value(name, value));
                else
                    modify_header_field(fields, name, value);
            }

            bool
            http_header_fields::get_header_field(header_fields &fields, const std::string &name, std::string &value)
            {
                bool get(false);

                if (fields.find(name) != fields.end())
                {
                    value = fields[name];
                    get = true;
                }

                return get;
            }

            bool
            http_header_fields::modify_header_field(header_fields &fields,
                                                    const std::string &name,
                                                    const std::string &value)
            {
                bool mod(false);

                if (fields.find(name) != fields.end())
                {
                    fields[name] = value;
                    mod = true;
                }

                return mod;
            }

            bool
            http_header_fields::is_empty_field(header_fields &fields, const std::string &name)
            {
                bool empty(true);

                if (fields.find(name) != fields.end())
                    empty = (fields[name].length() == 0);

                return empty;
            }

            std::string
            http_header_fields::field_to_string(header_fields &fields, const std::string &name)
            {
                std::stringstream ss;

                if (!is_empty_field(fields, name))
                    ss << name << colon << sp << fields[name] << crlf;

                return ss.str();
            }

            std::string
            http_header_fields::fields_to_string(header_fields &fields)
            {
                std::stringstream ss;

                for (header_fields_const_iterator it = fields.begin();
                     it != fields.end();
                     it++)
                    ss << field_to_string(fields, (*it).first);

                return ss.str();
            }

            // class functions

            http_header_fields::http_header_fields(const header_fields &fields)
            {
                for (header_fields_const_iterator it = fields.begin();
                     it != fields.end();
                     it++)
                    set_header_field((*it).first, (*it).second);
            }

            http_header_fields::http_header_fields(const http_header_fields &copy)
            {
                clone(copy);
            }

            http_header_fields &
            http_header_fields::operator=(const http_header_fields &rhs)
            {
                clone(rhs);

                return *this;
            }

            void
            http_header_fields::clone(const http_header_fields &copy)
            {
                http_header_.clear();

                header_fields fields = copy.get_header_fields();
                header_fields_const_iterator it = fields.begin();
                while (it != fields.end())
                {
                    insert_header_field(http_header_, (*it).first, (*it).second);
                    it++;
                }
            }

            bool
            http_header_fields::get_header_field(const std::string &name,
                                                 std::string &value)
            {
                return get_header_field(http_header_, name, value);
            }

            std::string
            http_header_fields::operator[](const std::string &name)
            {
                std::string value;
                get_header_field(name, value);

                return value;
            }

            void
            http_header_fields::set_header_field(const std::string &name, const std::string &value)
            {
                return insert_header_field(http_header_, name, value);
            }

            std::string
            http_header_fields::to_string(void)
            {
                return fields_to_string(http_header_);
            }
        }
    }
}
