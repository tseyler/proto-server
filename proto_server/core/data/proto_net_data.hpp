
#ifndef PROTO_NET_DATA_HPP_
#define PROTO_NET_DATA_HPP_

//
//  proto_net_data.hpp -
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <string>
#include <iostream>
#include <map>
//#include <boost/lockfree/spsc_queue.hpp>

namespace proto_net
{
    namespace data
    {
        typedef enum
        {
            data_unknown,
            data_text,
            data_binary,
            data_error,
        } proto_net_data_type;

        typedef enum
        {
            ec_success,              // no error
            ec_general_error,        // unspecified general error
            ec_data_size_error,      // data size error where the data is not available
            ec_connect_error,        // TCP connection error
            ec_read_error,           // error occurred while doing a read
            ec_write_timeout_error,  // write timeout error (no response)

        } proto_net_data_error_code;

        typedef std::map<proto_net_data_error_code, std::string> proto_net_error_code_map;

        class proto_net_data
        {
        public:

            proto_net_data(proto_net_data_type data_type = data_unknown);

            proto_net_data(size_t data_size,
                           proto_net_data_type data_type = data_unknown);

            proto_net_data(const char *data,
                           size_t data_size,
                           proto_net_data_type data_type = data_unknown);

            proto_net_data(const std::string &data, proto_net_data_type data_type = data_text);

            // copy constructor
            proto_net_data(const proto_net_data &copy_data);

            virtual ~proto_net_data();

            virtual proto_net_data &operator=(const proto_net_data &rhs);

            virtual proto_net_data &operator+=(const proto_net_data &rhs);

            virtual proto_net_data operator+(const proto_net_data &rhs);

            virtual bool operator==(const proto_net_data &rhs) const;

            virtual bool operator!=(const proto_net_data &rhs) const;

            virtual void clone(const proto_net_data &copy_data);

            virtual void append(const proto_net_data &append_data);

            virtual bool equals(const proto_net_data &rhs) const;

            virtual char* data(void) const;

            virtual size_t data_size(void) const;

            virtual proto_net_data_type data_type(void) const;

            virtual void data_type(proto_net_data_type type);

            virtual std::string to_string(void) const;

            //friend std::ostream& operator << (std::ostream& out, const proto_net_data& data);
            //friend std::istream& operator << (std::istream& in, proto_net_data& data);

        protected:

            void data_allocate(void);
            void data_clone(void);
            void data_copy(const char *data, size_t data_size);
            void data_resize(void); // used for resizing for text

        protected:

            char* data_;
            size_t data_size_;
            proto_net_data_type data_type_;
        };

        //std::ostream& operator << (std::ostream& out, const proto_net_data& data);
        //std::istream& operator >> (std::istream& in, proto_net_data& data);

        typedef proto_net_data proto_net_in_data;
        typedef proto_net_data proto_net_out_data;
        typedef proto_net_data proto_net_in_out_data;
        //typedef boost::lockfree::spsc_queue<proto_net_data> proto_net_data_queue;
    }

}

#endif