
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* InviteHandler.hpp                                                    	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef INVITEHANDLER_HPP_
#define INVITEHANDLER_HPP_

#include "sip/resip_dum.h"
#include "UserAgentCallbackImpl.hpp"
#include "SessionCallback.hpp"
#include "SessionDialog.hpp"

namespace SipUserAgent
{
	typedef enum
	{
		inviteInit,
		inviteClientSuccess,
		inviteServerSuccess,
		inviteFailure,
		inviteOffer,
		inviteOfferRequired,
		inviteConnected,
		inviteAnswer,
		inviteTerminated,
		inviteEarlyMedia,
		inviteProvisional,
		inviteMessageSuccess,
		inviteMessageFailure,
		inviteMessageReceived,
	} InviteResult;

	typedef IUserAgentCallback<InviteResult> IInviteCallback;
	typedef std::vector<IInviteCallback*> InviteCallbackCollection;
	typedef InviteCallbackCollection::iterator InviteCallbackIterator;
	typedef UserAgentCallbackImpl<InviteCallbackCollection, InviteCallbackIterator, IInviteCallback, InviteResult>
			InviteCallbackImpl;


	class InviteHandler : 	public InviteCallbackImpl,
							public resip::InviteSessionHandler
	{
	public:

		static std::string	terminatedReasonToString(resip::InviteSessionHandler::TerminatedReason r);

		InviteHandler() : 	InviteCallbackImpl(inviteInit),
							resip::InviteSessionHandler(false)
		{}

	    virtual void onNewSession(resip::ClientInviteSessionHandle, resip::InviteSession::OfferAnswerType oat, const resip::SipMessage& msg);
	    virtual void onNewSession(resip::ServerInviteSessionHandle, resip::InviteSession::OfferAnswerType oat, const resip::SipMessage& msg);
	    virtual void onFailure(resip::ClientInviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onEarlyMedia(resip::ClientInviteSessionHandle, const resip::SipMessage&, const resip::SdpContents&);
	    virtual void onProvisional(resip::ClientInviteSessionHandle, const resip::SipMessage&);
	    virtual void onConnected(resip::ClientInviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onConnected(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onTerminated(resip::InviteSessionHandle, resip::InviteSessionHandler::TerminatedReason reason, const resip::SipMessage* related);
	    virtual void onForkDestroyed(resip::ClientInviteSessionHandle);
	    virtual void onRedirected(resip::ClientInviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onAnswer(resip::InviteSessionHandle, const resip::SipMessage& msg, const resip::SdpContents&);
	    virtual void onOffer(resip::InviteSessionHandle, const resip::SipMessage& msg, const resip::SdpContents&);

		/** This method is called when an Invite w/out offer is sent, or any other context which
		 *   requires an offer from the user
		 *  @params InviteSessionHandle
		 *  	The handle for the inviteSession.
		 *  @params SipMessage
		 *  	The sipMessage containing the invite message details.
		 */
	    virtual void onOfferRequired(resip::InviteSessionHandle, const resip::SipMessage& msg);

	    virtual void onOfferRejected(resip::InviteSessionHandle, const resip::SipMessage* msg);
	    virtual void onInfo(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onInfoSuccess(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onInfoFailure(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onMessage(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onMessageSuccess(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onMessageFailure(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onRefer(resip::InviteSessionHandle, resip::ServerSubscriptionHandle, const resip::SipMessage& msg);
	    virtual void onReferNoSub(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onReferRejected(resip::InviteSessionHandle, const resip::SipMessage& msg);
	    virtual void onReferAccepted(resip::InviteSessionHandle, resip::ClientSubscriptionHandle, const resip::SipMessage& msg);

		// getters
	    /** Returns the actual SipMessage. */
	    resip::SipMessage getMessage() { return sipMessage; };

		SessionDialog*				getSessionDialog(const std::string& callId);

		// session callback
		void						addSessionCallback(ISessionCallback* sc);
		void						removeSessionCallback(ISessionCallback* sc);

	protected:

		void						fireSessionCallbacks(SessionStatus ss, SessionDialog* dialog);

		// session dialog
		std::string					addSessionDialog(resip::InviteSession* inviteSession);
		void						removeSessionDialog(const std::string& callId);

	protected:

	    SessionDialogMap			sessionDialogs_;
	    SessionCallbackCollection	sessionCallbacks_;

	    /** Stores the actual sipMessage. */
	    resip::SipMessage			sipMessage;

	};
}


#endif /* INVITEHANDLER_HPP_ */
