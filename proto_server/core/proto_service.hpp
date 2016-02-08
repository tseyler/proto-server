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
        virtual void ps_run(void) = 0;
        virtual void ps_stop(void) = 0;
    };

}
#endif //PROTO_SERVICE_HPP_
