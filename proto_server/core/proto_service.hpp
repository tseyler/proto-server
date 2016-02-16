//
// Created by tseyler on 2/8/16.
//

#ifndef PROTO_SERVICE_HPP_
#define PROTO_SERVICE_HPP_

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

}
#endif //PROTO_SERVICE_HPP_
