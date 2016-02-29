//
//  proto_sync_text_client.hpp - base class for synchronised IO for text tcp clients
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SYNC_TEXT_CLIENT_HPP_
#define PROTO_SYNC_TEXT_CLIENT_HPP_

#include <core/client/proto_client.hpp>

namespace proto_net
{
    namespace client
    {
        class proto_sync_text_client : public proto_client
        {
        public:

            proto_sync_text_client(const std::string& address, unsigned short port_num = 80,
                                proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                                size_t buffer_size = 4096);
            proto_sync_text_client(proto_net_service_ptr ps_service, const std::string& address,
                                    unsigned short port_num = 80,
                                    proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                                    size_t buffer_size = 4096);
            virtual ~proto_sync_text_client();

            virtual void ps_run(void);
            virtual void ps_stop(void);

            // synchronous reads and writes
            virtual void ps_write(proto_net_in_data& data_in);
            virtual void ps_read(proto_net_out_data& data_out);
            virtual void ps_write_read(proto_net_in_data& data_in, proto_net_out_data& data_out);

            // connect to a tcp server
            virtual void ps_connect(void) throw(proto_net_error_code);

            // getter
            proto_net_tcp_socket& ps_socket(void);

        protected:

            std::string address_;
            unsigned short port_num_;
            proto_net_tcp_socket socket_;
            proto_net_tcp_resolver resolver_;
            proto_net_pipeline& ps_pipeline_;
            size_t buffer_size_;
            char* buffer_;
            //proto_net_in_data write_data_;

            boost::asio::streambuf stream_buffer_;
        };
    }
}


#endif //PROTO_TCP_TEXT_CLIENT_HPP_
