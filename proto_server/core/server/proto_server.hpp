//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_SERVER_HPP__
#define PROTO_SERVER_HPP__

//#include <boost/shared_ptr.hpp>
//#include <boost/asio.hpp>

#include <core/proto_net_types.hpp>
#include <core/data/proto_net_io.hpp>
//#include <core/data/proto_net_data.hpp>

/*using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;*/
using namespace proto_net::data;

namespace proto_net
{
    namespace server
    {
        class proto_server
        {
        public:

            proto_server() { }
            // copy constructor

            virtual ~proto_server() {}

            // pure virtuals
            virtual void ps_run(void) = 0;
            virtual void ps_start_accept(proto_net_io& ps_io, size_t buffer_size) = 0;
        };
    }
}

#endif //PROTO_SERVER_HPP__

