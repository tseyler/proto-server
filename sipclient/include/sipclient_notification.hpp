//
// Created by tseyler on 2/9/16.
//

#ifndef SIPCLIENT_NOTIFICATION_HPP_
#define SIPCLIENT_NOTIFICATION_HPP_

#include <iostream>
#include <sstream>
#include "sipclient_notifier.hpp"
#include "sipclient_logger.hpp"


namespace sipclient
{

    class sipclient_notification;
    typedef std::shared_ptr<sipclient_notification> sipclient_notification_ptr;

    class sipclient_notification
    {
    public:

        sipclient_notification(sipclient_logger_ptr logger_ptr, sipclient_notifier* notifier_ptr);
        virtual ~sipclient_notification();

        virtual void sipclient_notify(layer_sipclient layer, unsigned short layer_event,
                                      const std::string& class_name, const std::string& function_name,
                                      int line, const std::string& notify_msg);
        virtual void sipclient_notify(layer_sipclient layer, unsigned short layer_event,
                                      const std::string& class_name, const std::string& function_name,
                                      int line, const std::stringstream& notify_stream);

    protected:

        void sipclient_log_msg(const std::string& class_name, const std::string& function_name, int line,
                               const std::string& log_msg);
        void sipclient_log_msg(const std::string& class_name, const std::string& function_name, int line,
                               const std::stringstream& log_stream);

    protected:

        sipclient_logger_ptr logger_ptr_;
        sipclient_notifier* notifier_ptr_;
    };

}
#endif //SIPCLIENT_NOTIFICATION_HPP_

