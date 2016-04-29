//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <boost/bind.hpp>
#include <core/server/proto_tcp_session.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {
        proto_tcp_session::proto_tcp_session(proto_net_service_ptr ps_service, proto_net_pipeline& ps_pipeline,
                                             size_t buffer_size /*= 4096*/) :
                proto_session(buffer_size),
                ps_pipeline_(ps_pipeline),
                socket_(proto_net_service_ref(ps_service)),
                session_read_error_(false)
        {}

        proto_tcp_session::~proto_tcp_session()
        {
            ps_close_session();
        }

        void
        proto_tcp_session::ps_start(void)
        {
            ps_async_read();
        }

        void
        proto_tcp_session::ps_async_read(void)
        {
            if (!session_read_error_)
            {
                socket_.async_read_some(boost::asio::buffer(buffer_, buffer_size_),
                                        boost::bind(&proto_tcp_session::ps_handle_read, this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
            }
            else
            {
                delete this;
            }
        }

        void
        proto_tcp_session::ps_async_write(proto_net_out_data& data_out)
        {
            if (data_out.data() && data_out.data_size()) //guard against empty data getting put into the pipe out
            {
                // add pre-write pipe out call for the pipeline
                ps_pipeline_.ps_pipe_out(data_out); // (server) any changes to the out data just prior to being sent
                char* data = data_out.data();
                size_t data_size = data_out.data_size();
                if (data && data_size)
                {
                    boost::asio::async_write(socket_, boost::asio::buffer(data, data_size),
                                             boost::bind(&proto_tcp_session::ps_handle_write, this,
                                                         boost::asio::placeholders::error));
                }
                else
                    ps_async_read(); // just go back to reading
            }
            else
                ps_async_read(); // just go back to reading
        }

        void
        proto_tcp_session::ps_handle_read(const boost::system::error_code &error, size_t bytes_transferred)
        {
            if (session_read_error_)
                return;

            if (!error)
            {
              // handle a ps_read here
                proto_net_data req_data(buffer_, bytes_transferred);
                proto_net_data res_data;
                if (req_data.data_size())
                {
                    ps_pipeline_.ps_pipe_in(req_data); // just prior to the pipeline execute the pipe in
                    ps_pipeline_.ps_pipeline(req_data, res_data); // all of the magic takes place inside the ps_io_ object
                }
                ps_async_write(res_data); // set response data ptr or size to zero for a non-write
            }
            else
            {
                ps_close_session();
                session_read_error_ = true;
            }
        }

        void
        proto_tcp_session::ps_handle_write(const boost::system::error_code &error)
        {
            if (!error)
            {
                // handle a post write here
                ps_async_read(); // just go back to reading
            }
            else
                delete this;
        }

        proto_net_pipeline&
        proto_tcp_session::ps_pipeline(void)
        {
            return ps_pipeline_;
        }

        proto_net_tcp_socket&
        proto_tcp_session::ps_socket(void)
        {
            return socket_;
        }

        void
        proto_tcp_session::ps_close_session(void)
        {
            if (socket_.is_open())
                socket_.close();
        }

        std::string
        proto_tcp_session::ps_client_address(void)
        {
            return socket_.remote_endpoint().address().to_string();
        }
    }

}