
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* UserAgent.hpp                                                       	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef USERAGENT_HPP_
#define USERAGENT_HPP_


#include <boost/thread.hpp>

#include "sip/resip_dum.h"
#include "sip/resip_dum_ssl.h"
#include "sip/resip_stack.h"
#include "sip/resip_stack_ssl.h"
#include "sip/rutil.h"

#include "RegistrationHandler.hpp"
#include "OutOfDialogHandler.hpp"
#include "InviteHandler.hpp"
#include "SubscriptionHandler.hpp"
#include "PublicationHandler.hpp"
#include "MessageHandler.hpp"

namespace SipUserAgent
{
    class UserAgent
    {
    public:

	UserAgent(int port, const char* passwd = NULL, resip::Security* security = NULL, bool bDisableUDP = true);
	UserAgent(const char* passwd = NULL, resip::Security* security = NULL);
	virtual ~UserAgent();

	// 	// setters
	void setRegistrationTime(unsigned int secs) { regRefreshSec_ = secs; }
	void setRegistrationRetryTime(unsigned int sec);
	void setKeepAliveTime(unsigned int udpSecs, unsigned int tcpSecs) { udpKeepAliveSec_ = udpSecs; tcpKeepAliveSec_ = tcpSecs; }
	void setProfileAor(const std::string& contact);
	void setAuthenticationManager(std::auto_ptr<resip::ClientAuthManager> authManager);
	void setPwd(const std::string& pwd) { pwd_ = resip::Data(pwd.c_str()); }
	void setDialogFactory(std::auto_ptr<resip::AppDialogSetFactory> factory);
	void setSupportedMethod(resip::MethodTypes type, const resip::Mime& mimeType);
	void setPublishStatus(bool online, const std::string& note = "");
	void setInstanceID(const std::string& uuid);

	void clearDialogSet();

	// getters
	// Get profile aor.
	resip::NameAddr& getProfileAor() const 	{ return profile_->getDefaultFrom(); }
	resip::SharedPtr<resip::DialogUsageManager> getDum(void) const { return dum_; }
	resip::SharedPtr<resip::SipStack> getStack(void) const { return stack_; }
	resip::SharedPtr<RegistrationHandler> getRegistrationHandler(void) const { return regHandler_; }
	resip::SharedPtr<OutOfDialogHandler> getOutOfDialogHandler(void) const { return oodHandler_; }
	resip::SharedPtr<InviteHandler> getInviteHandler(void) const { return inviteHandler_; }
	resip::SharedPtr<SubscriptionHandler> getSubscriptionHandler(void) const { return subscriptionHandler_; }
	resip::SharedPtr<PublicationHandler> getPublicationHandler(void) const { return publicationHandler_; }
	resip::SharedPtr<MessageHandler> getMessageHandler(void) const { return messageHandler_; }

	// SIP messages
	void registerUserAgent(bool forceRegistration = false);
	void unregisterUserAgent(void);
	void publishRequest(const std::string& serverURI, UInt32 expiresSeconds = 120);
	void optionRequest(const std::string& serverURI, resip::AppDialogSet* dialogSet = 0);
	void cancelRequest(const std::string& callId);
	void inviteRequest(const std::string& remoteURI, resip::SdpContents* sdp, resip::AppDialogSet* dialogSet = 0);
	void byeUserAgent(const std::string& callId, resip::InviteSession::EndReason reason = resip::InviteSession::UserHangup);
	void offerUserAgent(const std::string& callId, bool acceptCall = true, int statusCode = 200);
	void subscriptionRequest(const std::string& remoteURI, resip::AppDialogSet* dialogSet = 0);
	void subscriptionAllow(bool acceptSubscription = true);
//	void messageUserAgent(const std::string& message);	// in-session messaging
	void holdResumeRequest(const std::string& callId);	// hold / resume
	void sendInstantMessage(const std::string& remoteURI, const std::string& message);
	void shutdown(void);

	// replacement for IRunnable
	virtual void start(void);
	virtual void stop(void);
	virtual bool is_running(void) const;

    protected:

	virtual void setProfileAor(resip::NameAddr& nameAddr);
	virtual resip::SharedPtr<resip::SipMessage> makeRegistration(resip::NameAddr& aor);
	virtual resip::SharedPtr<resip::SipMessage> makeOptionRequest(resip::NameAddr& remoteAor,
								      resip::AppDialogSet* dialogSet = 0);
	virtual resip::SharedPtr<resip::SipMessage> makeInviteRequest(resip::NameAddr& remoteAor,
								      resip::SdpContents* sdp, resip::AppDialogSet* dialogSet = 0);
	virtual resip::SharedPtr<resip::SipMessage> makeSubscriptionRequest(resip::NameAddr& remoteAor,
									    resip::AppDialogSet* dialogSet = 0);
	virtual resip::SharedPtr<resip::SipMessage> makePublication(resip::NameAddr& aor, UInt32 expiresSeconds = 120);
	virtual resip::ServerSubscription* getServerSubscription(void) const;
	virtual SessionDialog* getSessionDialog(const std::string& callId) const;
	virtual void send(resip::SharedPtr<resip::SipMessage> message);

    protected:

	resip::SharedPtr<resip::SipStack> 	        stack_;
	resip::SharedPtr<resip::DialogUsageManager> 	dum_;
	resip::SharedPtr<resip::MasterProfile> 		profile_;
	resip::SharedPtr<RegistrationHandler> 		regHandler_;
	resip::SharedPtr<OutOfDialogHandler> 		oodHandler_;
	resip::SharedPtr<InviteHandler> 		inviteHandler_;
	resip::SharedPtr<SubscriptionHandler>		subscriptionHandler_;
	resip::SharedPtr<PublicationHandler>		publicationHandler_;
	resip::SharedPtr<MessageHandler>	        messageHandler_;
	resip::Data 					pwd_;
	resip::Pidf					pidf_;
	unsigned int 					regRefreshSec_;
	unsigned int 					udpKeepAliveSec_;
	unsigned int 					tcpKeepAliveSec_;
        resip::Transport*				pUDPTransport_;
	resip::Transport*				pTCPTransport_;


    private:
	    
	void initDum(int port, bool bDisableUDP);
	
	bool                                            running_;
	boost::thread*                                  p_thd_;
    };

    void useragent_thd(UserAgent* ua);

}

#endif /* USERAGENT_HPP_ */
