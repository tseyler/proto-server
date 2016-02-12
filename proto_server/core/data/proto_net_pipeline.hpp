//
// Created by Terry Seyler on 10/25/15.
//

#ifndef PROTO_NET_PIPELINE_HPP_
#define PROTO_NET_PIPELINE_HPP_

#include <core/proto_async_io.hpp>
#include <core/proto_service.hpp>
#include <core/data/proto_net_data.hpp>


namespace proto_net
{
    namespace data
    {
        class proto_net_pipeline
        {
        public:

            proto_net_pipeline() : ps_(NULL)
            {}
            virtual ~proto_net_pipeline()
            {}

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) = 0;  // the response data
            virtual void ps_pipe_in(proto_net_in_data& in_data) = 0;
            virtual void ps_pipe_out(proto_net_out_data& out_data) = 0;

            // getters
            proto_service*  ps_proto_service(void ) const { return ps_; }
            proto_async_io* ps_proto_io(void)const { return io_; }
            //setter
            void ps_proto_service(proto_service* ps) { ps_ = ps;}
            void ps_proto_io(proto_async_io* io) { io_ = io; }

        protected:

            proto_async_io* io_;

        private:

            proto_service* ps_;
        };

        // specialization with empty implementation
        class proto_net_empty_pipeline : public proto_net_pipeline
        {
        public:

            void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) {} // empty
            void ps_pipe_in(proto_net_in_data& in_data) {}
            void ps_pipe_out(proto_net_out_data& out_data) {}
        };

        extern proto_net_empty_pipeline empty_pipeline_inst;


    }
}
#endif //PROTO_NET_PIPELINE_HPP_
