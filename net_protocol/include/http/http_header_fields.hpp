/*
<boilerplate>



</boilerplate>
*/

#ifndef HTTP_HEADER_FIELDS_HPP_
#define HTTP_HEADER_FIELDS_HPP_

#include <map>
#include <string>

namespace proto_http
{
    typedef std::map<std::string, std::string> header_fields;
    typedef header_fields::iterator header_fields_iterator;
    typedef header_fields::const_iterator header_fields_const_iterator;
    typedef std::pair<std::string, std::string> header_name_value;

    class http_header_fields
    {
    public:

	// static functions
	static void insert_header_field(header_fields& fields,
				 const std::string& name, 
				 const std::string& value);
	static bool get_header_field(header_fields& fields,
			      const std::string& name, 
			      std::string& value);
	static bool modify_header_field(header_fields& fields,
				 const std::string& name, 
				 const std::string& value);
	static bool is_empty_field(header_fields& fields, 
			    const std::string& name);
	static std::string field_to_string(header_fields& fields, 
				    const std::string& name);
	static std::string fields_to_string(header_fields& fields);

	// class functions
	http_header_fields() { }
	http_header_fields(const header_fields& fields);
	http_header_fields(const http_header_fields& copy);
	http_header_fields& operator = (const http_header_fields& rhs);
	
	virtual void clone(const http_header_fields& copy);

	virtual bool get_header_field(const std::string& name, 
				      std::string& value);
	virtual std::string operator [] (const std::string& name);
	virtual void set_header_field(const std::string& name, 
				      const std::string& value);
	virtual header_fields get_header_fields(void) const { return http_header_; }
	virtual std::string to_string(void);
	size_t size(void) { return http_header_.size(); }
	void clear(void) { http_header_.clear(); }
    
    protected:

	virtual void init_header(void) { }

    protected:

	header_fields http_header_;
    };
}

#endif
