
#include <boost/bind.hpp>
#include <core/server/proto_tcp_session.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {
        proto_tcp_session::proto_tcp_session(proto_net_service_ptr ps_service, proto_net_pipeline& ps_pipeline,
                                             size_t buffer_size /*= 4096*/) :  proto_session(ps_pipeline, buffer_size),
                                                                               socket_(proto_net_service_ref(ps_service))
        {

        }

        proto_tcp_session::~proto_tcp_session()
        {

        }

        void
        proto_tcp_session::start(void)
        {
            read();
        }

        void
        proto_tcp_session::read(void)
        {

            socket_.async_read_some(boost::asio::buffer(buffer_, buffer_size_),
                                    boost::bind(&proto_tcp_session::handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }


        void
        proto_tcp_session::write(const char* data, size_t data_size)
        {
            if (data && data_size)
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(data, data_size),
                                         boost::bind(&proto_tcp_session::handle_write, this,
                                                     boost::asio::placeholders::error));
            else
                read(); // just go back to reading
        }

        void
        proto_tcp_session::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (!error)
            {
              // handle a read here
                proto_net_data req_data(buffer_, bytes_transferred);
                proto_net_data res_data;
                ps_pipeline_.ps_pipeline(req_data, res_data); // all of the magic takes place inside the ps_io_ object
                write(res_data.data(), res_data.data_size()); // set response data ptr or size to zero for a non-write
            }
            else
                delete this; // for now
        }

        void
        proto_tcp_session::handle_write(const boost::system::error_code& error)
        {
            if (!error)
            {
                // handle a post write here
                read(); // just go back to reading
            }
            else
                delete this;
        }

        proto_net_tcp_socket&
        proto_tcp_session::ps_socket(void)
        {
            return socket_;
        }
    }

}