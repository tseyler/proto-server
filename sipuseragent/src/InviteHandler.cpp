/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* InviteHandler.cpp                                                    	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include "userAgentHelper.h"
#include "userAgentCallbackCollection.h"
#include "InviteHandler.hpp"

using namespace resip;

std::string
SipUserAgent::InviteHandler::terminatedReasonToString(InviteSessionHandler::TerminatedReason r)
{
	std::string reason = "Unknown";
    switch (r)
    {
		case Error:

			reason = "Error";
			break;
		case Timeout:

			reason = "Timeout";
			break;
		case Replaced:

			reason = "Replaced";
			break;
		case LocalBye:

			reason = "Local Bye";
			break;
		case RemoteBye:

			reason = "Remote Bye";
			break;
		case LocalCancel:

			reason = "Local Bye";
			break;
		case RemoteCancel:

			reason = "Remote Cancel";
			break;
		case Rejected:

			reason = "Rejected";
			break;
		case Referred:

			reason = "Referred";
			break;
    }

    return reason;
}

void
SipUserAgent::InviteHandler::onNewSession(ClientInviteSessionHandle h, InviteSession::OfferAnswerType /*oat*/, const SipMessage& msg)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		std::string callId = SessionDialog::getCallId(h.get());
		addSessionDialog(h.get());
		setResult(inviteClientSuccess);
		fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
		fireSessionCallbacks(sNewSession, getSessionDialog(callId));
		LOG_UA_INFO( STD_STRING( "InviteHandler::onNewSession-Client" ), SipUserAgent::makeResponseString(msg) );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onNewSession-Client" ),
				STD_STRING( "Invalid client handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onNewSession(ServerInviteSessionHandle h, InviteSession::OfferAnswerType /*oat*/, const SipMessage& msg)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		h->provisional(180);		// 180 is a ringing provisional response -- remove after 2.7.2
		std::string callId = SessionDialog::getCallId(h.get());
		addSessionDialog(h.get());
		setResult(inviteServerSuccess);
		fireResult(SipUserAgent::makeString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
		fireSessionCallbacks(sNewSession, getSessionDialog(callId));
		LOG_UA_INFO( STD_STRING( "InviteHandler::onNewSession-Server" ), SipUserAgent::makeString(msg) );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onNewSession-Server" ),
				STD_STRING( "Invalid server handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onFailure(ClientInviteSessionHandle h, const SipMessage& msg)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		std::string callId = SessionDialog::getCallId(h.get());
		setResult(inviteFailure);
		fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);

		LOG_UA_WARNING( STD_STRING( "InviteHandler::onFailure" ), SipUserAgent::makeResponseString(msg) );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onFailure" ),
				STD_STRING( "Invalid client handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onEarlyMedia(ClientInviteSessionHandle h, const SipMessage& msg, const SdpContents& /*sdp*/)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		std::string callId = SessionDialog::getCallId(h.get());
		SipUserAgent::SessionDialog* dialog = getSessionDialog(callId);
		if (dialog)
		{
			setResult(inviteEarlyMedia);
			fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
			fireSessionCallbacks(sEarlyMedia, dialog);
			LOG_UA_INFO( STD_STRING( "InviteHandler::onEarlyMedia" ), SipUserAgent::makeResponseString(msg) );
		}
		else
			LOG_UA_ERROR( STD_STRING( "InviteHandler::onEarlyMedia" ),
					STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onEarlyMedia" ),
				STD_STRING( "Invalid client handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onProvisional(resip::ClientInviteSessionHandle h, const resip::SipMessage& msg)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		std::string callId = SessionDialog::getCallId(h.get());
		setResult(inviteProvisional);
		fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
		LOG_UA_INFO( STD_STRING( "InviteHandler::onProvisional" ), SipUserAgent::makeResponseString(msg) );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onProvisional" ),
				STD_STRING( "Invalid client handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onConnected(resip::ClientInviteSessionHandle h, const resip::SipMessage& msg)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		std::string callId = SessionDialog::getCallId(h.get());
		setResult(inviteConnected);
		fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
		LOG_UA_INFO( STD_STRING( "InviteHandler::onConnected-Client" ), SipUserAgent::makeResponseString(msg) );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onConnected" ),
				STD_STRING( "Invalid client handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onConnected(resip::InviteSessionHandle h, const resip::SipMessage& msg)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;
		std::string callId = SessionDialog::getCallId(h.get());
		setResult(inviteConnected);
		fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
		LOG_UA_INFO( STD_STRING( "InviteHandler::onConnected-Server" ), SipUserAgent::makeResponseString(msg) );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onConnected" ),
				STD_STRING( "Invalid handle: %s, line" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onTerminated(InviteSessionHandle h, InviteSessionHandler::TerminatedReason reason, const SipMessage* related)
{
	if (h.isValid())
	{
		// See if there is an exception thrown about SipMessage, if so, catch it.
		try
		{
			// Store the sip message in the class var.
			if (related)
				sipMessage = *related;
			else
				sipMessage = resip::SipMessage();
		}
		catch (...)
		{
			LOG_UA_INFO( STD_STRING( "InviteHandler::onTerminated exception was thrown." ),
					"sipMessage is invalid.") ;
		}

		std::string callId = SessionDialog::getCallId(h.get());
		SipUserAgent::SessionDialog* dialog = getSessionDialog(callId);
		if (dialog)
		{
			setResult(inviteTerminated);
			std::string msg = "Session terminated, reason: " + terminatedReasonToString(reason) + ", remote AOR: " + dialog->getRemoteUri();
			fireResult(msg, terminatedReasonToString(reason), SipUserAgent::makeStatusCode(sipMessage), callId);
			fireSessionCallbacks(sTerminated, dialog);
			removeSessionDialog(callId);
			LOG_UA_INFO( STD_STRING( "InviteHandler::onTerminated" ), msg );
		}
		else
			LOG_UA_ERROR( STD_STRING( "InviteHandler::onTerminated" ),
					STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onTerminated" ),
				STD_STRING( "Invalid session handle" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onForkDestroyed(ClientInviteSessionHandle)
{ }

void
SipUserAgent::InviteHandler::onRedirected(ClientInviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;

}

void
SipUserAgent::InviteHandler::onAnswer(InviteSessionHandle h, const SipMessage& msg, const SdpContents& sdp)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;

		std::string callId = SessionDialog::getCallId(h.get());
		SessionDialog* dialog = getSessionDialog(callId);
		if (dialog)
		{
			dialog->setRemoteSdp(new SessionSdp(const_cast<SdpContents*>(&sdp)));
			setResult(inviteAnswer);
			fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
			fireSessionCallbacks(sAnswer, getSessionDialog(callId));
			LOG_UA_INFO( STD_STRING( "InviteHandler::onAnswer" ), SipUserAgent::makeResponseString(msg) );
		}
		else
			LOG_UA_ERROR( STD_STRING( "InviteHandler::onAnswer" ),
					STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onAnswer" ),
				STD_STRING( "Invalid session handle" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onOffer(InviteSessionHandle h, const SipMessage& msg, const SdpContents& sdp)
{
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;

		std::string callId = SessionDialog::getCallId(h.get());
		SessionDialog* dialog = getSessionDialog(callId);
		if (dialog)
		{
			dialog->setRemoteSdp(new SessionSdp(const_cast<SdpContents*>(&sdp)));
			setResult(inviteOffer);
			fireResult(SipUserAgent::makeString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);
			fireSessionCallbacks(sOffer, getSessionDialog(callId));
			LOG_UA_INFO( STD_STRING( "InviteHandler::onOffer" ), SipUserAgent::makeString(msg) );
		}
		else
			LOG_UA_ERROR( STD_STRING( "InviteHandler::onOffer" ),
					STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onOffer" ),
				STD_STRING( "Invalid session handle" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onOfferRequired(resip::InviteSessionHandle h, const resip::SipMessage& msg)
{
	// Check that the handle is valid, else error.
	if (h.isValid())
	{
		// Store the sip message in the class var.
		sipMessage = msg;

		std::string callId = SessionDialog::getCallId(h.get());
		SessionDialog* dialog = getSessionDialog(callId);
		if (dialog)
		{
			// Set result, so the appropriate call back is triggered.
			setResult(inviteOfferRequired);

			// Fire OnResult call back.
			fireResult(SipUserAgent::makeString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg), callId);

			// Fire session call back.
			fireSessionCallbacks(sOfferRequired, getSessionDialog(callId));
			LOG_UA_INFO( STD_STRING( "InviteHandler::onOfferRequired" ), SipUserAgent::makeString(msg) );
		}
		else
			LOG_UA_ERROR( STD_STRING( "InviteHandler::onOfferRequired" ),
					STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "InviteHandler::onOfferRequired" ),
				STD_STRING( "Invalid session handle" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::InviteHandler::onOfferRejected(InviteSessionHandle, const SipMessage* msg)
{
	// Store the sip message in the class var.
	sipMessage = *msg;
}


void
SipUserAgent::InviteHandler::onInfo(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;

	setResult(inviteMessageReceived);
	fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg));
}

void
SipUserAgent::InviteHandler::onInfoSuccess(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;
}

void
SipUserAgent::InviteHandler::onInfoFailure(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;
}

void
SipUserAgent::InviteHandler::onMessage(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;

	setResult(inviteMessageReceived);
	fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg));
}

void
SipUserAgent::InviteHandler::onMessageSuccess(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;

	setResult(inviteMessageSuccess);
	fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg));
}

void
SipUserAgent::InviteHandler::onMessageFailure(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;

	setResult(inviteMessageFailure);
	fireResult(SipUserAgent::makeResponseString(msg), SipUserAgent::makeMethodString(msg), SipUserAgent::makeStatusCode(msg));
}

void
SipUserAgent::InviteHandler::onRefer(InviteSessionHandle, ServerSubscriptionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
		sipMessage = msg;
}

void
SipUserAgent::InviteHandler::onReferNoSub(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;
}

void
SipUserAgent::InviteHandler::onReferRejected(InviteSessionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;
}

void
SipUserAgent::InviteHandler::onReferAccepted(InviteSessionHandle, ClientSubscriptionHandle, const SipMessage& msg)
{
	// Store the sip message in the class var.
	sipMessage = msg;
}

void
SipUserAgent::InviteHandler::addSessionCallback(ISessionCallback* sc)
{
	addToCallbackCollection<SessionCallbackCollection, ISessionCallback>(sessionCallbacks_, sc);
}

void
SipUserAgent::InviteHandler::removeSessionCallback(ISessionCallback* sc)
{
	removeFromCallbackCollection<SessionCallbackCollection, SessionCallbackIterator, ISessionCallback>(sessionCallbacks_, sc);
}

void
SipUserAgent::InviteHandler::fireSessionCallbacks(SessionStatus ss, SessionDialog* dialog)
{
	SessionCallbackIterator it = sessionCallbacks_.begin();

	while (it != sessionCallbacks_.end())
	{
		ISessionCallback* cb = *it;
		cb->OnSessionChanged(ss, dialog);
		it++;
	}
}

SipUserAgent::SessionDialog*
SipUserAgent::InviteHandler::getSessionDialog(const std::string& callId)
{
	SessionDialogIterator it = sessionDialogs_.find(callId);

	return (it != sessionDialogs_.end()) ? it->second : NULL;
}

std::string
SipUserAgent::InviteHandler::addSessionDialog(resip::InviteSession* inviteSession)
{
	assert(inviteSession);
	std::string callId = SessionDialog::getCallId(inviteSession);
	sessionDialogs_[callId] = new SessionDialog(inviteSession);

	return callId;
}

void
SipUserAgent::InviteHandler::removeSessionDialog(const std::string& callId)
{
	SessionDialogIterator it = sessionDialogs_.find(callId);
	if (it != sessionDialogs_.end()) {
		delete it->second;
		sessionDialogs_.erase(it);
	}
}
