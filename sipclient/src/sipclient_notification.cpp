//
// Created by tseyler on 2/9/16.
//


#include "sipclient_notification.hpp"

namespace sipclient
{

    sipclient_notification::sipclient_notification(sipclient_logger_ptr logger_ptr,
                                                   sipclient_notifier* notifier_ptr) : logger_ptr_(logger_ptr),
                                                                                       notifier_ptr_(notifier_ptr)
    { }

    sipclient_notification::~sipclient_notification()
    { }

    void
    sipclient_notification::sipclient_notify(layer_sipclient layer, unsigned short layer_event,
                                  const std::string& class_name, const std::string& function_name,
                                  int line, const std::string& notify_msg)
    {
        sipclient_notification::sipclient_log_msg(class_name, function_name, line, notify_msg);
        if (notifier_ptr_)
            notifier_ptr_->sipclient_notify(layer, layer_event, notify_msg);
    }

    void
    sipclient_notification::sipclient_notify(layer_sipclient layer, unsigned short layer_event,
                                  const std::string& class_name, const std::string& function_name,
                                  int line, const std::stringstream& notify_stream)
    {
        sipclient_log_msg(class_name, function_name, line, notify_stream);
        if (notifier_ptr_)
            notifier_ptr_->sipclient_notify(layer, layer_event, notify_stream.str());
    }



    void sipclient_notification::sipclient_log_msg(const std::string& class_name, const std::string& function_name,
                                                   int line, const std::string& log_msg)
    {
        if (logger_ptr_)
            logger_ptr_->sipclient_log(class_name, function_name, line, log_msg);
    }

    void sipclient_notification::sipclient_log_msg(const std::string& class_name, const std::string& function_name,
                                                   int line, const std::stringstream& log_stream)
    {
        if (logger_ptr_)
            logger_ptr_->sipclient_log(class_name, function_name, line, log_stream);
    }
}

