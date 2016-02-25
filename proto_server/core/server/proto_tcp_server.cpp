
#include <boost/bind.hpp>
#include <core/server/proto_tcp_server.hpp>
#include <core/client/proto_tcp_client.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    using namespace data;
    using namespace client;

    namespace server
    {
        proto_tcp_server*
        proto_tcp_server::proto_tcp_server_cast(proto_service_ptr ps_ptr)
        {
            return dynamic_cast<proto_tcp_server*>(ps_ptr.get());
        }

        proto_async_io*
        proto_tcp_server::proto_async_io_cast(proto_service_ptr ps_ptr)
        {
            return dynamic_cast<proto_async_io*>(ps_ptr.get());
        }

        proto_tcp_server::proto_tcp_server(unsigned short port_num /* = 80*/)
                : port_num_(port_num),
                  acceptor_(proto_net_service_ref(ps_service_), proto_net_tcp_endpoint(tcp::v4(), port_num))
        {}

        proto_tcp_server::proto_tcp_server(proto_net_service_ptr ps_service, unsigned short port_num /*= 80*/)
                : proto_server(ps_service),
                  port_num_(port_num),
                  acceptor_(proto_net_service_ref(ps_service_), proto_net_tcp_endpoint(tcp::v4(), port_num))
        {}

        //TODO: need to fix where we get a copy of the ps_service_
        proto_tcp_server::proto_tcp_server(proto_tcp_server& ps)
                : port_num_(ps.ps_port()),
                  acceptor_(proto_net_service_ref(ps_service_), proto_net_tcp_endpoint(tcp::v4(), ps.ps_port()))
        {}

        unsigned short
        proto_tcp_server::ps_port(void) const
        {
            return port_num_;
        }

        void
        proto_tcp_server::ps_start_accept(proto_net_pipeline& ps_pipeline, size_t buffer_size)
        {
            proto_tcp_session* new_session = new proto_tcp_session(ps_service_, ps_pipeline, buffer_size);
            acceptor_.async_accept(new_session->ps_socket(),
                                   boost::bind(&proto_tcp_server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
        }

        void
        proto_tcp_server::handle_accept(proto_tcp_session* session, const proto_net_error_code& error)
        {
            if (session)
            {
                proto_net_pipeline& pipeline = session->ps_pipeline(); // get the session before it gets destroyed below
                proto_async_io* ds_io = pipeline.ps_proto_io();  // get the downstream io
                if (ds_io)
                {
                    proto_tcp_client* tcp_client = dynamic_cast<proto_tcp_client*>(ds_io); // we are tcp client?
                    {
                        proto_net_pipeline& upstream_pipeline = tcp_client->ps_pipeline();
                        upstream_pipeline.ps_proto_io(session); // set the upstream io to the session
                    }
                }
                size_t buffer_size = session->ps_buffer_size();
                if (!error)
                    session->ps_start();
                else
                    delete session;

                ps_start_accept(pipeline, buffer_size);
            }
            else {} // we will drop out because there is no session and no io
        }
    }



}
