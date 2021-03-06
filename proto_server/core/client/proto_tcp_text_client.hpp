//
//  proto_tcp_text_client.hpp - base class for tcp clients
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_TCP_TEXT_CLIENT_HPP_
#define PROTO_TCP_TEXT_CLIENT_HPP_

#include <core/client/proto_tcp_client.hpp>

namespace proto_net
{
    namespace client
    {
        class proto_tcp_text_client : public proto_tcp_client
        {
        public:

            static proto_tcp_text_client* proto_tcp_text_client_cast(proto_service_ptr ps_ptr);

            proto_tcp_text_client(const std::string& address, unsigned short port_num = 80,
                                proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                                size_t buffer_size = 4096);
            proto_tcp_text_client(proto_net_service_ptr ps_service, const std::string& address,
            unsigned short port_num = 80,
                    proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                    size_t buffer_size = 4096);
            virtual ~proto_tcp_text_client();

            // pure virtuals
            virtual void ps_async_read(void);
            virtual void ps_async_write(proto_net_in_data& data_in, bool no_write_complete = false);  //by default we set a flag for complete
            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error, size_t bytes_transferred);

        protected:

            boost::asio::streambuf read_stream_buffer_;
        };
    }
}


#endif //PROTO_TCP_TEXT_CLIENT_HPP_
