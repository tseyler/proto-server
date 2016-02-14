//
// Created by tseyler on 2/8/16.
//

#ifndef PROTO_SERVICE_HPP_
#define PROTO_SERVICE_HPP_

namespace proto_net
{
    class proto_service
    {
    public:
        // pure virtuals
        virtual void ps_run(void) = 0; // running service in same thread
        virtual void ps_start(void) = 0; // starting service in worker thread
        virtual void ps_stop(void) = 0;  // stopping service in worker thread
    };

}
#endif //PROTO_SERVICE_HPP_
