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
        signaling_event_sip_invite_client_success,
        signaling_event_sip_invite_server_success,
        signaling_event_sip_invite_failure,
        signaling_event_sip_invite_answer,
        signaling_event_sip_invite_connected,
        signaling_event_sip_invite_terminated,
        signaling_event_sip_invite_offer,
    };
}
#endif //SIPCLIENT_LAYER_EVENT_HPP_
