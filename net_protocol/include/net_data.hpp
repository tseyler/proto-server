/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef NET_DATA_HPP_
#define NET_DATA_HPP_


#include <string>

typedef enum { data_unknown, 
	       data_text, 
	       data_binary,
} net_data_type;

class net_data
{
public:

    net_data();
    net_data(const char* data,
	     size_t data_size, 
	     net_data_type data_type = data_unknown);
    net_data(const std::string& data);
    // copy constructor
    net_data(const net_data& copy_data);
    virtual ~net_data();
    net_data& operator = (const net_data& rhs);
    net_data& operator += (const net_data& rhs);
    net_data operator + (const net_data& rhs) const;
    bool operator == (const net_data& rhs) const;
    bool operator != (const net_data& rhs) const;
    virtual void clone(const net_data& copy_data);
    virtual void append(const net_data& append_data);
    virtual bool equals(const net_data& rhs) const;
    virtual char* data(void) const;
    virtual size_t data_size(void) const;
    net_data_type data_type(void) const;
    void data_type(net_data_type type);
    virtual std::string to_string(void) const;

private:

    void data_allocate(void);
    void data_copy(const char* data, 
		   size_t data_size);

protected:

    char* data_;
    size_t data_size_;
    net_data_type data_type_;	
};

#endif
