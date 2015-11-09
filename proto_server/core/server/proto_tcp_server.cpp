
#include <boost/bind.hpp>
#include <core/server/proto_tcp_server.hpp>

using namespace boost::asio::ip;

namespace proto_net
{
    namespace server
    {

        proto_tcp_server::proto_tcp_server(unsigned short port_num /* = 80*/) : proto_server(),
                                                                                io_tcp_object_(port_num)
        {

        }

        proto_tcp_server::proto_tcp_server(const proto_tcp_server& ps)
        {
            clone(ps);
        }

        proto_tcp_server&
        proto_tcp_server::clone(const proto_tcp_server& ps)
        {
            //proto_server::clone(dynamic_cast<const proto_server&>(ps));

            return *this;
        }

        proto_tcp_server&
        proto_tcp_server::operator =(const proto_tcp_server& ps)
        {
            return clone(ps);
        }

        void
        proto_tcp_server::ps_run(void)
        {
            io_tcp_object_.ps_io_service().run();
        }

        void
        proto_tcp_server::ps_start_accept(proto_net_io& ps_io)
        {

            proto_tcp_session* new_session = new proto_tcp_session(ps_io, io_tcp_object_.ps_io_port_num());
            io_tcp_object_.ps_acceptor().async_accept(new_session->ps_socket(),
                                   boost::bind(&proto_tcp_server::handle_accept, this, new_session, boost::asio::placeholders::error));
        }

        void
        proto_tcp_server::handle_accept(proto_tcp_session* session, const boost::system::error_code& error)
        {
            if (!error)
                session->start();
            else
                delete session;

            ps_start_accept(session->ps_io());
        }
    }



}
