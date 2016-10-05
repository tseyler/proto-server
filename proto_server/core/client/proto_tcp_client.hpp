//
//  proto_tcp_client.hpp - base class for tcp clients
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_CLIENT_HPP_
#define PROTO_TCP_CLIENT_HPP_

#include <core/proto_async_io.hpp>
#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        class proto_tcp_client : public proto_async_io, public proto_client
        {
        public:

            static proto_tcp_client* proto_tcp_client_cast(proto_service_ptr ps_ptr);
            static proto_async_io* proto_async_io_cast(proto_service_ptr ps_ptr);

            proto_tcp_client(const std::string& address, unsigned short port_num = 80,
                             proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                             size_t buffer_size = 4096);
            proto_tcp_client(proto_net_service_ptr ps_service, const std::string& address,
                             unsigned short port_num = 80,
                             proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                             size_t buffer_size = 4096);
            virtual ~proto_tcp_client();

            // pure virtuals - ps_async_io
            virtual void ps_async_read(void);
            virtual void ps_async_write(proto_net_in_data& data_in);
            virtual proto_net_pipeline& ps_pipeline(void);

            virtual void ps_async_connect(const proto_net_in_data& write__data);
            virtual void ps_handle_resolve(const boost::system::error_code &error,
                                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
            virtual void ps_handle_connect(const boost::system::error_code &error,
                                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error, size_t bytes_transferred);

            virtual bool ps_write_complete(size_t max_wait_msec = 2000);

            // getter
            proto_net_tcp_socket_ptr ps_socket(void);
            size_t ps_max_wait(void) const;
            // setter
            void ps_max_wait(size_t max_wax_msec);
            bool ps_is_connected(void) const { return connected_; }

        protected:

            std::string address_;
            unsigned short port_num_;
            proto_net_tcp_socket_ptr socket_;
            proto_net_tcp_resolver resolver_;
            proto_net_pipeline& ps_pipeline_;
            size_t buffer_size_;
            char* buffer_;
            proto_net_in_data write_data_;
            volatile bool write_complete_;
            size_t max_wait_msec_;
            bool connected_;
        };
    }
}


#endif //PROTO_TCP_CLIENT_HPP_
