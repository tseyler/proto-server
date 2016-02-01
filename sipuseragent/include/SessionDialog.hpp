
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SessionDialog.hpp                                                    	    *
* Author: Terry Seyler							                            *
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

		static unsigned long		gen_session_id(void);

		SessionDialog(resip::InviteSession* inviteSession);
		virtual ~SessionDialog()
		{}

		// setters
		void 						setSessionSdp(SessionSdpPtr sessionSdp);
		void 						setRemoteSdp(SessionSdpPtr remoteSdp);

		// getters
		SessionSdpPtr				getSessionSdp(void) const { return sessionSdp_; }
		SessionSdpPtr				getRemoteSdp(void) const { return remoteSdp_; }
		std::string					getCallId(void) const { return callId_; }
		resip::InviteSession*		getInviteSession(void) const { return inviteSession_; }
		OnHold						getHoldStatus(void) const;
		std::string					getLocalUri(void) const;
		std::string					getRemoteUri(void) const;
		std::string					getLocalUser(void) const;
		std::string					getRemoteUser(void) const;
		std::string					getLocalHost(void) const;
		std::string					getRemoteHost(void) const;
		unsigned long				get_session_id(void) const;

		/**	Method returns the remoteAor.
		 * 	@return remoteAor as NameAddr. */
		resip::NameAddr				getRemoteAor(void) const;

	protected:

		void						negotiateMedia(void);

	protected:

		resip::InviteSession*				inviteSession_;
		SessionSdpPtr						sessionSdp_;
		std::shared_ptr<SessionSdp>			remoteSdp_;
		std::string							callId_;
		unsigned long						session_id_;

	private:

		static unsigned long				session_id_counter_;
	};

}


#endif /* SESSIONDIALOG_HPP_ */
