
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* UserAgent.cpp                                                             *
* Author: Terry Seyler						      	                        *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <cassert>
#include <sstream>
#include "UserAgent.hpp"

using namespace resip;

SipUserAgent::UserAgent::UserAgent(int port, const char* passwd /*= NULL*/, resip::Security* security /*= NULL*/,  bool bDisableUDP /*= true*/) :
    stack_(security ? new SipStack(security) : new SipStack),
    dum_(new DialogUsageManager(*stack_)),
    profile_(new MasterProfile),
    regHandler_(new SipUserAgent::RegistrationHandler),
    oodHandler_(new SipUserAgent::OutOfDialogHandler),
    inviteHandler_(new SipUserAgent::InviteHandler),
    subscriptionHandler_(new SipUserAgent::SubscriptionHandler),
    publicationHandler_(new SipUserAgent::PublicationHandler),
    messageHandler_(new SipUserAgent::MessageHandler),
    pwd_(Data(passwd)),
    regRefreshSec_(3600),
    udpKeepAliveSec_(30),
    tcpKeepAliveSec_(120),
    pUDPTransport_(NULL),
    pTCPTransport_(NULL),
    running_(false),
    p_thd_(NULL)
{
	initDum(port, bDisableUDP);
}

SipUserAgent::UserAgent::UserAgent(const char* passwd /*= NULL*/, resip::Security* security /*= NULL*/) :
    stack_(security ? new SipStack(security) : new SipStack),
    dum_(new DialogUsageManager(*stack_)),
    profile_(new MasterProfile),
    regHandler_(new SipUserAgent::RegistrationHandler),
    oodHandler_(new SipUserAgent::OutOfDialogHandler),
    inviteHandler_(new SipUserAgent::InviteHandler),
    subscriptionHandler_(new SipUserAgent::SubscriptionHandler),
    publicationHandler_(new SipUserAgent::PublicationHandler),
    messageHandler_(new SipUserAgent::MessageHandler),
    pwd_(Data(passwd)),
    regRefreshSec_(3600),
    udpKeepAliveSec_(30),
    tcpKeepAliveSec_(120),
    pUDPTransport_(NULL),
    pTCPTransport_(NULL),
    running_(false),
    p_thd_(NULL)
{
 	initDum(0, false);
}

void
SipUserAgent::UserAgent::initDum(int port, bool bDisableUDP)
{
 	assert(dum_.get());

	// Create the transports ourselves (rather than tell the DUM to do it) so that we have pointers to them:
	pTCPTransport_ = dum_->getSipStack().addTransport(TCP, port, V4);
	if(!bDisableUDP)
		pUDPTransport_ = dum_->getSipStack().addTransport(UDP, port, V4);

#ifdef USE_SSL
	dum_->addTransport(TLS, 0, V4);
#endif
	dum_->setMasterProfile(profile_);

	assert(regHandler_.get());
	dum_->setClientRegistrationHandler(reinterpret_cast<ClientRegistrationHandler*>(regHandler_.get()));
	assert(oodHandler_.get());
	dum_->addOutOfDialogHandler(OPTIONS, reinterpret_cast<resip::OutOfDialogHandler*>(oodHandler_.get()));
	assert(inviteHandler_.get());
	dum_->setInviteSessionHandler(reinterpret_cast<InviteSessionHandler*>(inviteHandler_.get()));
	assert(subscriptionHandler_.get());
	dum_->addClientSubscriptionHandler("presence", subscriptionHandler_.get());
	dum_->addServerSubscriptionHandler("presence", subscriptionHandler_.get());
	assert(publicationHandler_.get());
	dum_->addClientPublicationHandler("presence", publicationHandler_.get());
	assert(messageHandler_.get());
	dum_->setClientPagerMessageHandler(messageHandler_.get());
	dum_->setServerPagerMessageHandler(messageHandler_.get());
}

SipUserAgent::UserAgent::~UserAgent()
{ 
    stop();
}

void
SipUserAgent::UserAgent::setProfileAor(const std::string& contact)
{
	NameAddr nameAddr = SipUserAgent::makeNameAddr(contact);
	setProfileAor(nameAddr);
}

void
SipUserAgent::UserAgent::setProfileAor(NameAddr& nameAddr)
{
	assert(profile_.get());
	profile_->setDefaultFrom(nameAddr);
	profile_->setDigestCredential(nameAddr.uri().host(), nameAddr.uri().user(), pwd_);

	// Disable RInstance.
	profile_->setRinstanceEnabled(false);

	profile_->addSupportedOptionTag(Token(Symbols::Outbound));  // RFC 5626 - outbound
	profile_->addSupportedOptionTag(Token(Symbols::Path));      // RFC 3327 - path
	profile_->setOutboundProxy(nameAddr.uri());

	profile_->setExpressOutboundAsRouteSetEnabled(true);
	profile_->setKeepAliveTimeForDatagram(udpKeepAliveSec_);
	profile_->setKeepAliveTimeForStream(tcpKeepAliveSec_);

	profile_->setInstanceId(nameAddr.displayName());  // See RFC5626 section 4.1
	profile_->setRegId(0);

	profile_->clientOutboundEnabled() = true;

	dum_->setKeepAliveManager(std::auto_ptr<KeepAliveManager>(new KeepAliveManager));
}

void
SipUserAgent::UserAgent::setAuthenticationManager(std::auto_ptr<ClientAuthManager> authManager)
{
	assert(dum_.get());
	dum_->setClientAuthManager(authManager);
}

void
SipUserAgent::UserAgent::setDialogFactory(std::auto_ptr<AppDialogSetFactory> factory)
{
	assert(dum_.get());
	dum_->setAppDialogSetFactory(factory);
}

void
SipUserAgent::UserAgent::setSupportedMethod(resip::MethodTypes type, const resip::Mime& mimeType)
{
	assert(dum_.get());
	dum_->getMasterProfile()->addSupportedMethod(type);
	dum_->getMasterProfile()->addSupportedMimeType(type, mimeType);
}

void
SipUserAgent::UserAgent::setPublishStatus(bool online, const std::string& note /*= ""*/)
{
	pidf_.setSimpleStatus(online, SipUserAgent::makeData(note));
	publicationHandler_->getClientPublication()->update(&pidf_);
}

void
SipUserAgent::UserAgent::setInstanceID(const std::string& uuid)
{
	assert(profile_.get());
	profile_->setInstanceId(Data(uuid.c_str()));
}

void
SipUserAgent::UserAgent::setRegistrationRetryTime(unsigned int sec)
{
	assert(regHandler_.get());
	regHandler_->setRegistrationRetryTime(sec);
}

void
SipUserAgent::UserAgent::registerUserAgent(bool forceRegistration/* = false*/)
{
	assert(dum_.get());
	assert(regHandler_.get());

	if (forceRegistration)
		regHandler_->resetRegistration();

	if (regHandler_->getResult() == regInit)
	{
		LOG_UA_INFO( STD_STRING( "UserAgent::registerUserAgent" ), STD_STRING( "Registering useragent") );
		profile_->setDefaultRegistrationTime(regRefreshSec_);
		profile_->setDefaultRegistrationRetryTime(regHandler_->getRegistrationRetryTime());

		SharedPtr<SipMessage> regMessage = makeRegistration(profile_->getDefaultFrom());
		send(regMessage);
	}
	else
		LOG_UA_WARNING(  STD_STRING( "UserAgent::registerUserAgent" ), STD_STRING( "Useragent is either registered or is attempting to register") );
}

void
SipUserAgent::UserAgent::unregisterUserAgent(void)
{
	assert(regHandler_.get());

	LOG_UA_INFO( STD_STRING( "UserAgent::registerUserAgent" ), STD_STRING( "Unregistering useragent") );
	regHandler_->unRegister();
}

void
SipUserAgent::UserAgent::publishRequest(const std::string& serverURI, UInt32 expiresSeconds /*= 120*/)
{
	NameAddr serverAor(serverURI.c_str());
	SharedPtr<SipMessage> pubMessage = makePublication(serverAor, expiresSeconds);
	send(pubMessage);
}

void
SipUserAgent::UserAgent::optionRequest(const std::string& serverURI, AppDialogSet* dialogSet /*= 0*/)
{
	NameAddr serverAor(serverURI.c_str());
	SharedPtr<SipMessage> oodMessage = makeOptionRequest(serverAor, dialogSet);
	send(oodMessage);
}

void
SipUserAgent::UserAgent::cancelRequest(const std::string& callId)
{
	SessionDialog* dialog = getSessionDialog(callId);
	if (dialog)
	{
		InviteSession* is = dialog->getInviteSession();
		if (is)
		{
			std::stringstream ss;
			ss << "CANCEL sent to remote AOR: " << dialog->getRemoteUri();
			LOG_UA_INFO( STD_STRING( "UserAgent::cancelRequest" ), ss.str() );

			is->getAppDialogSet()->end();
		}
		else
			LOG_UA_ERROR( STD_STRING( "UserAgent::cancelRequest" ),
					STD_STRING( "Null session pointer" ), STD_STRING( __FILE__ ), __LINE__ );

	}
	else
		LOG_UA_ERROR( STD_STRING( "UserAgent::cancelRequest" ),
				STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::UserAgent::inviteRequest(const std::string& remoteURI, resip::SdpContents* sdp, AppDialogSet* dialogSet /*= 0*/)
{
	NameAddr remoteAor(remoteURI.c_str());

	std::stringstream ss;
	ss << "INVITE sent to remote AOR: " << remoteAor;
	LOG_UA_INFO( STD_STRING( "UserAgent::inviteRequest" ), ss.str() );

	SharedPtr<SipMessage> inviteMessage = makeInviteRequest(remoteAor, sdp, dialogSet);
	send(inviteMessage);
}

void
SipUserAgent::UserAgent::byeUserAgent(const std::string& callId, InviteSession::EndReason reason /*= UserHangup*/)
{
	SessionDialog* dialog = getSessionDialog(callId);
	if (dialog)
	{
		InviteSession* is = dialog->getInviteSession();
		if (is)
		{
			std::stringstream ss;
			ss << "BYE sent to remote AOR: " << dialog->getRemoteUri() << ", Reason code: " << reason;
			LOG_UA_INFO( STD_STRING( "UserAgent::byeUserAgent" ), ss.str() );

			is->end(reason);
		}
		else
			LOG_UA_ERROR( STD_STRING( "UserAgent::byeUserAgent" ),
					STD_STRING( "Null session pointer" ), __FILE__, __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "UserAgent::byeUserAgent" ),
				STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::UserAgent::offerUserAgent(const std::string& callId, bool acceptCall /*= true*/, int statusCode /*= 200*/)
{
	SessionDialog* dialog = getSessionDialog(callId);
	if (dialog)
	{
		InviteSession* is = dialog->getInviteSession();
		if (is)
		{
			// if I am a server then I receive the call
			ServerInviteSession* sis = dynamic_cast<ServerInviteSession*>(is);
			if (sis)
			{
				std::stringstream ss;
				if (acceptCall)
				{
					sis->accept();
					ss << "Accepted call from remote AOR: " << dialog->getRemoteUri();
				}
				else
				{
					sis->reject(statusCode);
					ss << "Rejected call, Status code: " << statusCode;
				}
				LOG_UA_INFO( STD_STRING( "UserAgent::offerUserAgent" ), ss.str() );
			}
			else
				LOG_UA_ERROR( STD_STRING( "UserAgent::offerUserAgent" ),
						STD_STRING( "No server session exists for that dialog" ), STD_STRING( __FILE__ ), __LINE__ );
		}
		else
			LOG_UA_ERROR( STD_STRING( "UserAgent::offerUserAgent" ),
					STD_STRING( "No session exists for that dialog" ), STD_STRING( __FILE__ ), __LINE__ );
	}
	else
		LOG_UA_ERROR( STD_STRING( "UserAgent::offerUserAgent" ),
				STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::UserAgent::subscriptionRequest(const std::string& remoteURI, resip::AppDialogSet* dialogSet /*= 0*/)
{
	NameAddr remoteAor(remoteURI.c_str());

	SharedPtr<SipMessage> subscribeMessage = makeSubscriptionRequest(remoteAor, dialogSet);
	send(subscribeMessage);
}

void
SipUserAgent::UserAgent::subscriptionAllow(bool acceptSubscription /*= true*/)
{
	ServerSubscription* serverSubscribe = getServerSubscription();

	if (serverSubscribe)
	{
		SharedPtr<SipMessage> msg = acceptSubscription ? serverSubscribe->accept() : serverSubscribe->reject(400);
		serverSubscribe->send(msg);
	}
}

/*
void // send an in-session message
SipUserAgent::UserAgent::messageUserAgent(const std::string& message)
{

	InviteSession* is = getInviteSession();
	if (is)
	{
		PlainContents contents(message.c_str());
		is->message(contents);
	}
}
*/


void
SipUserAgent::UserAgent::holdResumeRequest(const std::string& callId)
{
	SessionDialog* dialog = getSessionDialog(callId);
	if (dialog)
	{
		SessionSdpPtr sessionSdp = dialog->getSessionSdp();
		if (sessionSdp)
		{
			// get our current SendRecv
			SessionSdp::SdpMedia* media = sessionSdp->getFrontMedia();
			if (media)
			{
				SessionSdp::SdpMedia::SendRecv sr(SessionSdp::SdpMedia::srNotSpecified);
				switch (media->getSendRecv())	// below are the two case we are interested in
				{
					case SessionSdp::SdpMedia::srSendRecv:

						sr = SessionSdp::SdpMedia::srSend;		// set to sendonly
					break;
					case SessionSdp::SdpMedia::srSend:

						sr = SessionSdp::SdpMedia::srSendRecv;	// set to send recv - resume
					break;
					case SessionSdp::SdpMedia::srNotSpecified:
					case SessionSdp::SdpMedia::srInactive:
					case SessionSdp::SdpMedia::srRecv:

					break;
				}
				if (sr != SessionSdp::SdpMedia::srNotSpecified)
				{
					InviteSession* is = dialog->getInviteSession();
					if (is)
					{
						std::stringstream ss;
						ss << "Re-INVITE sent to remote AOR: " << dialog->getRemoteUri();
						LOG_UA_INFO( STD_STRING( "UserAgent::holdResumeRequest" ), ss.str() );

						// change the media to the new sendrecv
						media->addSendRecvAttribute(sr);
						std::auto_ptr<Contents> contents(sessionSdp->toSdpContents().clone());
						is->provideOffer(*contents);
					}
					else
						LOG_UA_ERROR( STD_STRING( "UserAgent::holdResumeRequest" ),
								STD_STRING( "No session exists for that dialog" ), STD_STRING( __FILE__ ), __LINE__ );
				}
			}
		}
	}
	else
		LOG_UA_ERROR( STD_STRING( "UserAgent::holdResumeRequest" ),
				STD_STRING( "No dialog exists for that call ID" ), STD_STRING( __FILE__ ), __LINE__ );
}

void
SipUserAgent::UserAgent::sendInstantMessage(const std::string& remoteURI, const std::string& message)
{
	assert(dum_.get());

	NameAddr remoteAor(remoteURI.c_str());
	ClientPagerMessageHandle cpmh = dum_->makePagerMessage(remoteAor);

	std::auto_ptr<Contents> content(new PlainContents(SipUserAgent::makeData(message)));
	cpmh.get()->page(content);
}

void
SipUserAgent::UserAgent::shutdown(void)
{
	assert(dum_.get());
    dum_->shutdown(NULL);
    assert(regHandler_.get());
    regHandler_->stopRegistering();
}

SharedPtr<SipMessage>
SipUserAgent::UserAgent::makeRegistration(NameAddr& aor)
{
	assert(dum_.get());
	return dum_->makeRegistration(aor);
}

SharedPtr<SipMessage>
SipUserAgent::UserAgent:: makePublication(resip::NameAddr& aor, UInt32 expiresSeconds /*= 120*/)
{
	assert(dum_.get());

	pidf_.setSimpleStatus(true);
	pidf_.setEntity(aor.uri());
	pidf_.setSimpleId(Random::getCryptoRandomHex(3));

	return dum_->makePublication(aor, profile_, pidf_, "presence", expiresSeconds);
}

SharedPtr<SipMessage>
SipUserAgent::UserAgent::makeOptionRequest(NameAddr& remoteAor, AppDialogSet* dialogSet /*= 0*/)
{
	assert(dum_.get());
	return dum_->makeOutOfDialogRequest(remoteAor, OPTIONS, dialogSet);
}

SharedPtr<SipMessage>
SipUserAgent::UserAgent::makeInviteRequest(NameAddr& remoteAor, SdpContents* sdp, AppDialogSet* dialogSet /*= 0*/)
{
	assert(dum_.get());
    return dum_->makeInviteSession(remoteAor, sdp, dialogSet);
}

SharedPtr<SipMessage>
SipUserAgent::UserAgent::makeSubscriptionRequest(NameAddr& remoteAor, AppDialogSet* dialogSet /*= 0*/)
{
	assert(dum_.get());
	return dum_->makeSubscription(remoteAor, "presence", dialogSet);
}

SipUserAgent::SessionDialog*
SipUserAgent::UserAgent::getSessionDialog(const std::string& callId) const
{
	assert(inviteHandler_.get());

	return  inviteHandler_->getSessionDialog(callId);
}

ServerSubscription*
SipUserAgent::UserAgent::getServerSubscription(void) const
{
	assert(subscriptionHandler_.get());
	return subscriptionHandler_->getServerSubscription();
}

void
SipUserAgent::UserAgent::send(resip::SharedPtr<resip::SipMessage> message)
{
	assert(dum_.get());
	dum_->send(message);
}

void
SipUserAgent::UserAgent::clearDialogSet()
{
	assert(dum_.get());
	//dum_->clearDialogSet(); this may be deprecated
}

void
SipUserAgent::UserAgent::start(void)
{
    stop(); // stop it 

    
    p_thd_ = new boost::thread(&SipUserAgent::useragent_thd, this);
    running_ = true;
 
}

void
SipUserAgent::UserAgent::stop(void)
{
    running_ = false;
    
    if (p_thd_)
	p_thd_->join();
   
    delete p_thd_;
    p_thd_ = NULL;
}

bool
SipUserAgent::UserAgent::is_running(void) const
{
    return running_;
}

void
SipUserAgent::useragent_thd(UserAgent* ua)
{
    assert(ua);
    SharedPtr<DialogUsageManager> dum = ua->getDum();
    assert(dum.get());
    SharedPtr<SipStack> stack = ua->getStack();
    assert(stack.get());

#ifndef WIN32
     Log::initialize(Log::Syslog, Log::Debug, "SipUserAgent");
#endif

    while (ua->is_running())
    {
		stack->process(100);
		while (dum->process()); // now dum processes I/O until it has nothing left to do
    }
}
