//
// Created by tseyler on 1/13/16.
//
#include <ostream>
#include <istream>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <core/client/proto_tcp_text_client.hpp>


namespace proto_net
{
    namespace client
    {
        proto_tcp_text_client::proto_tcp_text_client(const std::string& address,
                                           unsigned short port_num /* = 80*/,
                                           proto_net_pipeline& ps_pipeline/* = empty_pipeline_inst*/,
                                           size_t buffer_size /*= 4096*/)
                : proto_tcp_client(address, port_num, ps_pipeline, buffer_size)
        {
        }

        proto_tcp_text_client::~proto_tcp_text_client()
        {
        }

        void
        proto_tcp_text_client::ps_async_read(void)
        {
            boost::asio::async_read_until(socket_, stream_buffer_, '\0',
                                          boost::bind(&proto_tcp_text_client::ps_handle_read, this,
                                                      boost::asio::placeholders::error,
                                                      boost::asio::placeholders::bytes_transferred));
        }

        void
        proto_tcp_text_client::ps_async_write(proto_net_in_data& data_in)
        {
            ps_pipeline_.ps_pipe_in(data_in); // just prior to the write, execute the pipe_in
            if (data_in.data_type() != data_text)
            {
                ps_async_read(); // just go back to reading
                return;
            }

            char* data = data_in.data();
            size_t data_size = data_in.data_size();
            if (data && data_size)
            {
                data_size++; // increase by 1
                boost::asio::async_write(socket_, boost::asio::buffer(data, data_size),
                                         boost::bind(&proto_tcp_text_client::ps_handle_write, this,
                                                     boost::asio::placeholders::error));
            }
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_text_client::ps_handle_read(const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (!error)
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
                    ps_async_write(req_data);
                }
            }
            else
                delete this; // for now
        }

        void
        proto_tcp_text_client::ps_handle_write(const boost::system::error_code &error)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
            else
                delete this;
        }

        void
        proto_tcp_text_client::ps_write(proto_net_in_data& data_in)
        {
            ps_pipeline_.ps_pipe_in(data_in); // just prior to the write, execute the pipe_in
            if (data_in.data_type() != data_text)
                return;

            char* data = data_in.data();
            size_t data_size = data_in.data_size();
            if (data && data_size)
            {
                data_size++; // increase by 1
                boost::asio::write(socket_, boost::asio::buffer(data, data_size));
            }
        }

        void
        proto_tcp_text_client::ps_read(proto_net_out_data& data_out)
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

        void proto_tcp_text_client::ps_write_read(proto_net_in_data& data_in, proto_net_out_data& data_out)
        {
            ps_write(data_in);
            ps_read(data_out);
        }


    }
}