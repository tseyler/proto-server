
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SessionDialog.cpp                                                    	    *
* Author: Terry Seyler							                            *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include "SessionDialog.hpp"

using namespace resip;

std::string
SipUserAgent::SessionDialog::getCallId(resip::InviteSession* inviteSession)
{
	assert(inviteSession);

	return SipUserAgent::makeString(inviteSession->getCallId());
}

unsigned long SipUserAgent::SessionDialog::session_id_counter_ = 0;
unsigned long
SipUserAgent::SessionDialog::gen_session_id(void)
{
	return ++session_id_counter_;
}

SipUserAgent::SessionDialog::SessionDialog(resip::InviteSession* inviteSession) : 	inviteSession_(inviteSession),
																					sessionSdp_(NULL),
																					remoteSdp_(NULL),
																					callId_(""),
																					session_id_(gen_session_id())
{
	callId_ = getCallId(inviteSession);
}

SipUserAgent::SessionDialog::OnHold
SipUserAgent::SessionDialog::getHoldStatus(void) const
{
	OnHold oh(ohNotSpecified);

	if (sessionSdp_.get() && remoteSdp_.get())
	{
		SessionSdp::SdpMedia* sessionMedia = sessionSdp_->getFrontMedia();
		SessionSdp::SdpMedia* remoteMedia = remoteSdp_->getFrontMedia();

		if (sessionMedia && remoteMedia)
		{
			SessionSdp::SdpMedia::SendRecv remoteSendRecv = remoteMedia->getSendRecv();

			switch (remoteSendRecv)
			{
				case SessionSdp::SdpMedia::srSend:

					if (sessionMedia->sendRecvAttributeExists(SessionSdp::SdpMedia::srRecv))
						oh = ohRemoteHold;
				break;
				case SessionSdp::SdpMedia::srRecv:

					if (sessionMedia->sendRecvAttributeExists(SessionSdp::SdpMedia::srSend))
						oh = ohLocalHold;
				break;
				case SessionSdp::SdpMedia::srSendRecv:

					oh = ohNoHold;
				break;
				case SessionSdp::SdpMedia::srNotSpecified:
				case SessionSdp::SdpMedia::srInactive:

				break;
			}
		}
	}

	return oh;
}

void
SipUserAgent::SessionDialog::setSessionSdp(SessionSdpPtr sessionSdp)
{
	sessionSdp_ = sessionSdp;
	negotiateMedia();
}

void
SipUserAgent::SessionDialog::setRemoteSdp(SessionSdpPtr remoteSdp)
{
	remoteSdp_ = remoteSdp;
	negotiateMedia();				// negotiate after setting the remote
}

void
SipUserAgent::SessionDialog::negotiateMedia(void)
{
	if (sessionSdp_ && remoteSdp_)	// perform the negotiation - need both to negotiate
	{
		SdpContents contents = remoteSdp_->toSdpContents();
		sessionSdp_->negotiateMedia(&contents);
	}
}

std::string
SipUserAgent::SessionDialog::getLocalUri(void) const
{
	return (inviteSession_) ? SipUserAgent::makeAor(inviteSession_->myAddr().uri()) : "";
}

std::string
SipUserAgent::SessionDialog::getRemoteUri(void) const
{
	return (inviteSession_) ? SipUserAgent::makeAor(inviteSession_->peerAddr().uri()) : "";
}

NameAddr
SipUserAgent::SessionDialog::getRemoteAor(void) const
{
	return (inviteSession_) ? inviteSession_->peerAddr() : NameAddr("");
}


std::string
SipUserAgent::SessionDialog::getLocalUser(void) const
{
	return (inviteSession_) ? SipUserAgent::makeUser(inviteSession_->myAddr().uri()) : "";
}

std::string
SipUserAgent::SessionDialog::getRemoteUser(void) const
{
	return (inviteSession_) ? SipUserAgent::makeUser(inviteSession_->peerAddr().uri()) : "";
}

std::string
SipUserAgent::SessionDialog::getLocalHost(void) const
{
	return (inviteSession_) ? SipUserAgent::makeHost(inviteSession_->myAddr().uri()) : "";
}

std::string
SipUserAgent::SessionDialog::getRemoteHost(void) const
{
	return (inviteSession_) ? SipUserAgent::makeHost(inviteSession_->peerAddr().uri()) : "";
}

unsigned long
SipUserAgent::SessionDialog::get_session_id(void) const
{
	return session_id_;
}

