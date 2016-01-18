
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SessionDialog.hpp                                                    	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef SESSIONDIALOG_HPP_
#define SESSIONDIALOG_HPP_

#include <string>
#include <map>
#include "sip/resip_dum.h"
#include "SessionSdp.hpp"
#include "userAgentHelper.h"


namespace SipUserAgent
{
	class SessionDialog;
	typedef std::map<std::string, SessionDialog*>	SessionDialogMap;
	typedef SessionDialogMap::iterator				SessionDialogIterator;

	class SessionDialog
	{
	public:

		enum OnHold {				ohNotSpecified,
									ohNoHold,
									ohLocalHold,
									ohRemoteHold,
		};

		static std::string			getCallId(resip::InviteSession* inviteSession);

		SessionDialog(resip::InviteSession* inviteSession);
		virtual ~SessionDialog()
		{}

		// setters
		void 						setSessionSdp(SessionSdp* sessionSdp);
		void 						setRemoteSdp(SessionSdp* remoteSdp);

		// getters
		SessionSdp*					getSessionSdp(void) const { return sessionSdp_.get(); }
		SessionSdp*					getRemoteSdp(void) const { return remoteSdp_.get(); }
		std::string					getCallId(void) const { return callId_; }
		resip::InviteSession*		getInviteSession(void) const { return inviteSession_; }
		OnHold						getHoldStatus(void) const;
		std::string					getLocalUri(void) const;
		std::string					getRemoteUri(void) const;
		std::string					getLocalUser(void) const;
		std::string					getRemoteUser(void) const;
		std::string					getLocalHost(void) const;
		std::string					getRemoteHost(void) const;

		/**	Method returns the remoteAor.
		 * 	@return remoteAor as NameAddr. */
		resip::NameAddr				getRemoteAor(void) const;

	protected:

		void						negotiateMedia(void);

	protected:

		resip::InviteSession*				inviteSession_;
	    std::auto_ptr<SessionSdp>			sessionSdp_;
	    std::auto_ptr<SessionSdp>			remoteSdp_;
		std::string							callId_;
	};

}


#endif /* SESSIONDIALOG_HPP_ */
