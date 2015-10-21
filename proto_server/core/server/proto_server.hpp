//
// Created by Terry Seyler on 8/19/15.
//

#ifndef PROTO_SERVER_HPP__
#define PROTO_SERVER_HPP__

# include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <core/proto_constants.h>
#include <core/proto_io_object.hpp>
#include <core/data/proto_net_data.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
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
            //proto_server(const proto_server& ps);

            virtual ~proto_server() {}

           // proto_server& clone(const proto_server& ps);

          //  proto_server& operator =(const proto_server& ps);

            // pure virtuals
            virtual void ps_initialize(void) = 0;
            virtual void ps_run(void) = 0;
            virtual void ps_pipe(const proto_net_data& req_data, proto_net_data& res_data) = 0;

            // getters
           // unsigned short ps_port_number(void) const;

        protected:

            virtual void ps_start_accept(void) = 0;

        protected:

            //Proto_IO_Object io_object_;
           // unsigned short port_num_;
           // int af_protocol_family_;
        };
    }
}

#endif //PROTO_SERVER_HPP__

