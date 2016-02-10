//
// Created by tseyler on 2/10/16.
//

#ifndef SIPCLIENT_NOTIFIER_HPP_
#define SIPCLIENT_NOTIFIER_HPP_


namespace sipclient
{
    enum layer_sipclient {layer_signaling, layer_media, layer_ui};

    class sipclient_notifier
    {
    public:

        virtual void sipclient_notify(layer_sipclient layer, unsigned short layer_event,
                                      const std::string& notify_msg) = 0;
    };

}

#endif //SIPCLIENT_NOTIFIER_HPP_
