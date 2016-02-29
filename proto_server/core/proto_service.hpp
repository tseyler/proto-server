//
//  proto_service.hpp - interface for clients and servers
//  part of the proto-server library
//
//  Copyright (c) 2015, 2016 Terry Seyler
//
//  Distributed under the MIT License
//  See accompanying file LICENSE.md
//

#ifndef PROTO_SERVICE_HPP_
#define PROTO_SERVICE_HPP_

#include <boost/shared_ptr.hpp>

namespace proto_net
{
    /**
     * \brief proto_service: Pure abstract class for clients and servers.
     * The proto_service class is implemented by the base classes proto_server and proto_client.
     */
    class proto_service
    {
    public:
        // pure virtuals
        /**
         * Runs the underlying boost::asio::io_service in its own thread.
         */
        virtual void ps_run(void) = 0; // running service in same thread
        /**
        * When implemented starts the underlying boost::asio::io_service in a worker thread and then returns.
        */
        virtual void ps_start(void) = 0; // starting service in worker thread
        /**
        * When implemented stops the underlying boost::asio::io_service and joins the worker thread to the main process thread.
        */
        virtual void ps_stop(void) = 0;  // stopping service in worker thread
    };

    typedef boost::shared_ptr<proto_service> proto_service_ptr;

}
#endif //PROTO_SERVICE_HPP_
