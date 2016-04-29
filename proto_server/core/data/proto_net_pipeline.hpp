
#ifndef PROTO_NET_PIPELINE_HPP_
#define PROTO_NET_PIPELINE_HPP_

//
//  proto_net_pipeline.hpp -
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#include <core/proto_async_io.hpp>
#include <core/proto_service.hpp>
#include <core/data/proto_net_data.hpp>
#include <core/data/proto_net_error_data.hpp>
#include <core/proto_net_types.hpp>


namespace proto_net
{
    namespace data
    {
        class proto_net_pipeline
        {
        public:

            proto_net_pipeline();
            virtual ~proto_net_pipeline();

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) = 0;  // the response data
            virtual void ps_pipe_in(proto_net_in_data& in_data) = 0;
            virtual void ps_pipe_out(proto_net_out_data& out_data) = 0;
            // returns whether if error is fatal or not true | false
            virtual bool ps_pipe_error(proto_net_error_data& error_data) = 0;

            // getters
            proto_service*  ps_proto_service(void ) const;
            proto_async_io* ps_proto_io(void) const;

            //setter
            void ps_proto_service(proto_service* ps);
            void ps_proto_io(proto_async_io* io);


        protected:

            proto_async_io* io_;
            proto_net_mutex mutex_;

        private:

            proto_service* ps_;
        };

        // specialization with empty implementation
        class proto_net_empty_pipeline : public proto_net_pipeline
        {
        public:

            virtual void ps_pipeline(const proto_net_in_data& req_data, proto_net_out_data& res_data) {} // empty
            virtual void ps_pipe_in(proto_net_in_data& in_data) {}
            virtual void ps_pipe_out(proto_net_out_data& out_data) {}
            virtual bool ps_pipe_error(proto_net_error_data& error_data) { return false; } // never fatal for empty pipeline
        };

        extern proto_net_empty_pipeline empty_pipeline_inst;

        typedef boost::shared_ptr<proto_net_pipeline> proto_pipeline_ptr;


    }
}
#endif //PROTO_NET_PIPELINE_HPP_
