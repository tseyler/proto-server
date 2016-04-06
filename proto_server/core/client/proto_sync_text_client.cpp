//
//  Copyright (c) 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <ostream>
#include <istream>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <core/client/proto_sync_text_client.hpp>


namespace proto_net
{
    namespace client
    {
        proto_sync_text_client::proto_sync_text_client(const std::string& address,
                                           unsigned short port_num /* = 80*/,
                                           proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                           size_t buffer_size /*= 4096*/)
                : address_(address),  port_num_(port_num), socket_(proto_net_service_ref(ps_service_)),
                  resolver_(proto_net_service_ref(ps_service_)),
                  ps_pipeline_(ps_pipeline),
                  buffer_size_(buffer_size),
                  buffer_(NULL)
        {
            buffer_ = buffer_size_ ? new char[buffer_size_] : NULL;
        }

        proto_sync_text_client::~proto_sync_text_client()
        {}

        proto_sync_text_client::proto_sync_text_client(proto_net_service_ptr ps_service, const std::string& address,
                                                     unsigned short port_num /* = 80*/,
                                                     proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                                     size_t buffer_size /*= 4096*/)
                : proto_client(ps_service), address_(address),  port_num_(port_num),
                  socket_(proto_net_service_ref(ps_service_)),
                  resolver_(proto_net_service_ref(ps_service_)),
                  ps_pipeline_(ps_pipeline),
                  buffer_size_(buffer_size),
                  buffer_(NULL)
        {
            buffer_ = buffer_size_ ? new char[buffer_size_] : NULL;
        }

        void
        proto_sync_text_client::ps_run(void)
        {
            //Not implemented
        }

        void
        proto_sync_text_client::ps_stop(void)
        {
            //Not implemented
        }

        void
        proto_sync_text_client::ps_connect(void) throw(proto_net_error_code)
        {
            proto_net_tcp_resolver resolver(proto_net_service_ref(ps_service_));
            std::string port_str = boost::lexical_cast<std::string>(port_num_);
            proto_net_tcp_query query(address_.c_str(), port_str.c_str());
            proto_net_tcp_iterator iterator = ps_tcp_resolve(resolver, query);

            ps_tcp_connect(socket_, iterator);
        }

        void
        proto_sync_text_client::ps_write(proto_net_in_data& data_in)
        {
            if (data_in.data() && data_in.data_size() && data_in.data_type() == data_text) //guard against empty data getting put into the pipe in
            {
                ps_pipeline_.ps_pipe_in(data_in); // just prior to the write, execute the pipe_in
                char *data = data_in.data();
                size_t data_size = data_in.data_size();
                if (data && data_size) {
                    data_size++; // increase by 1
                    boost::asio::write(socket_, boost::asio::buffer(data, data_size));
                }
            }
        }

        void
        proto_sync_text_client::ps_read(proto_net_out_data& data_out)
        {
            if (boost::asio::read_until(socket_, stream_buffer_, '\0'))
            {
                std::istream is(&stream_buffer_);
                is.get(buffer_, buffer_size_, '\0');
                // handle a ps_read here
                proto_net_data req_data;
                req_data.data_type(data_text);
                proto_net_data res_data(buffer_, strlen(buffer_));
                res_data.data_type(data_text);
                if (res_data.data_size())
                {
                    ps_pipeline_.ps_pipeline(res_data, req_data); // response and request are reversed here
                    ps_pipeline_.ps_pipe_out(res_data); // post read, execute the pipe_out for the client
                }
            }
        }

        void proto_sync_text_client::ps_write_read(proto_net_in_data& data_in, proto_net_out_data& data_out)
        {
            ps_write(data_in);
            ps_read(data_out);
        }

    }
}