/*
  <boilerplate>



  </boilerplate>
*/

#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <net_data.hpp>

net_data::net_data() : data_(0),
		 data_size_(0),
		 data_type_(data_unknown)
{}

net_data::net_data(const char* data,
		   size_t data_size, 
		   net_data_type data_type) : data_(0),
					      data_size_(data_size),
					      data_type_(data_type)
{
    data_allocate();		
    data_copy(data, data_size);
}

net_data::net_data(const std::string& data) : data_(0),
					      data_size_(data.length()),
					      data_type_(data_text)
{
    data_allocate();		
    data_copy(data.c_str(), data_size_);
}

net_data::net_data(const net_data& copy_data) : data_(0),
					       data_size_(0),
					       data_type_(data_unknown)
{
    clone(copy_data);
}

net_data::~net_data()
{
    delete [] data_;
}

net_data& 
net_data::operator = (const net_data& rhs)
{
    if (&rhs != this)
	clone(rhs);

    return *this;
}

net_data& 
net_data::operator += (const net_data& rhs)
{
    append(rhs);

    return *this;
}

net_data 
net_data::operator + (const net_data& rhs) const
{
    net_data result = *this;
    result.append(rhs);

    return result;
}

bool 
net_data::operator == (const net_data& rhs) const
{
    return equals(rhs);
}

bool 
net_data::operator != (const net_data& rhs) const
{
    return !equals(rhs);
}

void 
net_data::clone(const net_data& copy_data)
{
    data_size_ = copy_data.data_size();
    data_type_ = copy_data.data_type();
    if (data_size_)
    {
	data_allocate();
	data_copy(copy_data.data(), data_size_);
    }
}

void 
net_data::append(const net_data& append_data)
{
    if (append_data.data_size() > 0)
    {
	// change data type to unknown
	data_type(data_unknown);
	net_data copy_data(append_data);
	copy_data.data_type(data_unknown);
	size_t new_size = data_size_ + copy_data.data_size();
	char new_data[new_size];
	memset(&new_data, 0, new_size);
	memcpy(&new_data, data_, data_size_);
	char* offset_ptr = new_data + data_size_;
	memcpy(offset_ptr, copy_data.data(), copy_data.data_size());
	clone(net_data(new_data, new_size));
    }
}

bool net_data::equals(const net_data& rhs) const
{
    bool result(false);

    if (data_type_ == rhs.data_type() && 
	data_size_ == rhs.data_size())
	result = (memcmp(data_, rhs.data(), data_size_) == 0);

    return result;
}

char* 
net_data::data(void) const 
{ 
    return data_; 
}

size_t 
net_data::data_size(void) const 
{ 
    return data_size_; 
}

net_data_type 
net_data::data_type(void) const 
{ 
    return data_type_;
}

void 
net_data::data_type(net_data_type type)
{
    data_type_ = type;
}

std::string 
net_data::to_string(void) const
{
    std::ostringstream ss;
    switch (data_type_)
    {
    case data_text:
    {
	size_t sz = data_size_ + 1;
	char str[sz];
	memset(str, 0, sz);
	memcpy(str, data_, data_size_); 
	ss << std::string(str);
    }
    break;
    case data_unknown:
    case data_binary:
    {
	ss << std::setw(2) << std::setfill('0') << std::hex;
	for (size_t t = 0; t < data_size_; t++)
	    ss << static_cast<unsigned int>(data_[t]);
    }
    break;
    }

    return ss.str();
}

void 
net_data::data_allocate(void)
{
    delete [] data_;
    data_ = new char[data_size_];
    memset(data_, 0, data_size_);
}

void 
net_data::data_copy(const char* data, 
		    size_t data_size)
{
    if (data_size <= data_size_)
	memcpy(data_, data, data_size);
}
