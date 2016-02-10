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

    }

    void
    sipclient_notification::sipclient_notify(layer_sipclient layer, unsigned short layer_event,
                                  const std::string& class_name, const std::string& function_name,
                                  int line, const std::stringstream& notify_stream)
    {

    }



    void sipclient_notification::sipclient_log_msg(const std::string& class_name, const std::string& function_name,
                                                   int line, const std::string& log_msg)
    {

    }

    void sipclient_notification::sipclient_log_msg(const std::string& class_name, const std::string& function_name,
                                                   int line, const std::stringstream& log_stream)
    {

    }
}

