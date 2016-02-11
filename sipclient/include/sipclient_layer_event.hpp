//
// Created by tseyler on 2/11/16.
//

#ifndef SIPCLIENT_LAYER_EVENT_HPP_
#define SIPCLIENT_LAYER_EVENT_HPP_

namespace sipclient
{

    enum sipclient_signaling_event
    {
        signaling_event_sip_registration_success,
        signaling_event_sip_registration_failure,
        signaling_event_sip_client_call_success,
    };
}
#endif //SIPCLIENT_LAYER_EVENT_HPP_
