
#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <core/data/proto_net_data.hpp>

namespace proto_net
{
    namespace data
    {
        proto_net_data::proto_net_data(proto_net_data_type data_type /*= data_unknown*/) : data_(0),
                                                                                            data_size_(0),
                                                                                            data_type_(data_type)
        {}

        proto_net_data::proto_net_data(size_t data_size,
                                       proto_net_data_type data_type /*= data_unknown*/) : data_(0),
                                                                                           data_size_(data_size),
                                                                                           data_type_(data_type)
        {
            data_allocate();
        }

        proto_net_data::proto_net_data(const char* data, size_t data_size,
                                       proto_net_data_type data_type) : data_(0),
                                                                          data_size_(data_size),
                                                                          data_type_(data_type)
        {
            data_allocate();
            data_copy(data, data_size);
        }

        proto_net_data::proto_net_data(const std::string& data, proto_net_data_type data_type /*= data_text*/) :
                data_(0), data_size_(data.length()), data_type_(data_type)
        {
            data_allocate();
            data_copy(data.c_str(), data_size_);
        }

        proto_net_data::proto_net_data(const proto_net_data& copy_data) : data_(0), data_size_(0), data_type_(data_unknown)
        {
            clone(copy_data);
        }

        proto_net_data::~proto_net_data()
        {
            delete [] data_;
        }

        proto_net_data&
        proto_net_data::operator = (const proto_net_data& rhs)
        {
            if (&rhs != this)
                clone(rhs);

            return *this;
        }

        proto_net_data&
        proto_net_data::operator += (const proto_net_data& rhs)
        {
            append(rhs);

            return *this;
        }

        proto_net_data
        proto_net_data::operator + (const proto_net_data& rhs) const
        {
            proto_net_data result = *this;
            result.append(rhs);

            return result;
        }

        bool
        proto_net_data::operator == (const proto_net_data& rhs) const
        {
            return equals(rhs);
        }

        bool
        proto_net_data::operator != (const proto_net_data& rhs) const
        {
            return !equals(rhs);
        }

        void
        proto_net_data::clone(const proto_net_data& copy_data)
        {
            data_size_ = copy_data.data_size();
            data_type_ = copy_data.data_type();
            if (data_size_)
            {
                data_clone();
                data_copy(copy_data.data(), data_size_);
            }
        }

        void
        proto_net_data::append(const proto_net_data& append_data)
        {
            if (append_data.data_size() > 0)
            {
                // change data type to unknown
                data_type(data_unknown);
                proto_net_data copy_data(append_data);
                copy_data.data_type(data_unknown);
                size_t new_size = data_size_ + copy_data.data_size();
                char new_data[new_size];
                memset(&new_data, 0, new_size);
                memcpy(&new_data, data_, data_size_);
                char* offset_ptr = new_data + data_size_;
                memcpy(offset_ptr, copy_data.data(), copy_data.data_size());
                clone(proto_net_data(new_data, new_size));
            }
        }

        bool
        proto_net_data::equals(const proto_net_data& rhs) const
        {
            bool result(false);

            if (data_type_ == rhs.data_type() &&
                data_size_ == rhs.data_size())
                result = (memcmp(data_, rhs.data(), data_size_) == 0);

            return result;
        }

        char*
        proto_net_data::data(void) const
        {
            return data_;
        }

        size_t
        proto_net_data::data_size(void) const
        {
            return data_size_;
        }

        proto_net_data_type
        proto_net_data::data_type(void) const
        {
            return data_type_;
        }

        void
        proto_net_data::data_type(proto_net_data_type type)
        {
            if (data_type_ != type)
            {
                switch (type)
                {
                    case data_text:

                        if (type != data_error) // then we need to re-allocate
                            data_resize();
                        break;
                    case data_error:

                        if (type != data_text)
                            data_resize();
                        break;
                    case data_binary:
                    case data_unknown:

                        // nothing to do
                        break;
                }

                data_type_ = type;
            }
        }

        std::string
        proto_net_data::to_string(void) const
        {
            std::ostringstream ss;
            switch (data_type_)
            {
                case data_text:
                case data_error:
                {
                    size_t sz = data_size_; // + 1;
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
        proto_net_data::data_allocate(void)
        {
            delete [] data_;

            if (data_size_)
            {
                if (data_type_ == data_text || data_type_ == data_error)
                    data_size_++;

                data_ = new char[data_size_];
                memset(data_, 0, data_size_);
            }
        }

        void
        proto_net_data::data_clone(void)
        {
            delete [] data_;

            if (data_size_)
            {
                data_ = new char[data_size_];
                memset(data_, 0, data_size_);
            }
        }

        void
        proto_net_data::data_copy(const char* data,
                                  size_t data_size)
        {
            if (data_size <= data_size_)
                memcpy(data_, data, data_size);
        }

        void
        proto_net_data::data_resize(void)
        {
            size_t sz = data_size_ + 1;
            char str[sz];
            memset(str, 0, sz);
            memcpy(str, data_, data_size_);
            data_size_ = sz;
        }

        std::ostream&
        operator << (std::ostream& out, const proto_net_data& data)
        {
            out << data.to_string();

            return out;
        }

        std::istream&
        operator >> (std::istream& in, proto_net_data& data)
        {
            std::stringstream ss;
            char c;
            while (in)
            {
                in >> c;
                ss << c;
            }
            // assign the input to data
            data = proto_net_data(ss.str());

            return in;
        }
    }
}
