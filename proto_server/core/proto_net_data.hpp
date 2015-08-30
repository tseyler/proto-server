/*
	Copyright 2015 Terry Seyler.  All rights reserved.
*/

#ifndef PROTO_NET_DATA_HPP__
#define PROTO_NET_DATA_HPP__


#include <string>

namespace proto_net
{
    typedef enum
    {
        data_unknown,
        data_text,
        data_binary,
    } proto_net_data_type;

    class proto_net_data
    {
    public:

        proto_net_data();

        proto_net_data(const char *data,
                 size_t data_size,
                       proto_net_data_type data_type = data_unknown);

        proto_net_data(const std::string &data);

        // copy constructor
        proto_net_data(const proto_net_data &copy_data);

        virtual ~proto_net_data();

        proto_net_data &operator=(const proto_net_data &rhs);

        proto_net_data &operator+=(const proto_net_data &rhs);

        proto_net_data operator+(const proto_net_data &rhs) const;

        bool operator==(const proto_net_data &rhs) const;

        bool operator!=(const proto_net_data &rhs) const;

        virtual void clone(const proto_net_data &copy_data);

        virtual void append(const proto_net_data &append_data);

        virtual bool equals(const proto_net_data &rhs) const;

        virtual char* data(void) const;

        virtual size_t data_size(void) const;

        proto_net_data_type data_type(void) const;

        void data_type(proto_net_data_type type);

        virtual std::string to_string(void) const;

    private:

        void data_allocate(void);

        void data_copy(const char *data,
                       size_t data_size);

    protected:

        char *data_;
        size_t data_size_;
        proto_net_data_type data_type_;
    };
}

#endif