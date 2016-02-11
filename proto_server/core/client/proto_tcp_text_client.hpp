//
// Created by tseyler on 1/13/16.
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

            proto_tcp_text_client(const std::string& address, unsigned short port_num = 80,
                                proto_net_pipeline& ps_pipeline = empty_pipeline_inst,
                                size_t buffer_size = 4096);
            virtual ~proto_tcp_text_client();

            // pure virtuals
            //virtual void ps_async_connect(const proto_net_in_data& write__data);
            virtual void ps_async_read(void);
            virtual void ps_async_write(proto_net_in_data& data_in);

//            virtual void ps_handle_resolve(const boost::system::error_code &error,
//                                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
//            virtual void ps_handle_connect(const boost::system::error_code &error,
//                                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
            virtual void ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred);
            virtual void ps_handle_write(const boost::system::error_code &error);

        protected:

            boost::asio::streambuf stream_buffer_;
        };
    }
}


#endif //PROTO_TCP_TEXT_CLIENT_HPP_