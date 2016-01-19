
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SubscriptionHandler.cpp                                                   *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include "userAgentHelper.h"
#include "userAgentCallbackCollection.h"
#include "SubscriptionHandler.hpp"

using namespace resip;

void
SipUserAgent::SubscriptionHandler::onUpdatePending(ClientSubscriptionHandle h, const SipMessage& notify, bool /*outOfOrder*/)
{
	h->acceptUpdate();
	setResult(subscribeUpdatePending);
	fireResult(SipUserAgent::makeMsgBodyString(notify), "SUBSCRIBE", 200);
}

void
SipUserAgent::SubscriptionHandler::onUpdateActive(ClientSubscriptionHandle h, const SipMessage& notify, bool /*outOfOrder*/)
{
	h->acceptUpdate();
	setResult(subscribeUpdateActive);
	fireResult(SipUserAgent::makeMsgBodyString(notify), SipUserAgent::makeMethodString(notify), SipUserAgent::makeStatusCode(notify));
}

void
SipUserAgent::SubscriptionHandler::onUpdateExtension(ClientSubscriptionHandle h, const SipMessage& notify, bool /*outOfOrder*/)
{
	h->acceptUpdate();
	setResult(subscribeUpdateExtension);
	fireResult(SipUserAgent::makeMsgBodyString(notify), SipUserAgent::makeMethodString(notify), SipUserAgent::makeStatusCode(notify));
}

int
SipUserAgent::SubscriptionHandler::onRequestRetry(ClientSubscriptionHandle, int, const SipMessage&)
{
	return -1;
}

void
SipUserAgent::SubscriptionHandler::onTerminated(ClientSubscriptionHandle, const SipMessage*)
{
	setResult(subscribeTerminated);
	fireResult("Terminated", "SUBSCRIBE", 200);
}

void
SipUserAgent::SubscriptionHandler::onNewSubscription(ClientSubscriptionHandle, const SipMessage&)
{ }

void
SipUserAgent::SubscriptionHandler::onNewSubscription(ServerSubscriptionHandle h, const SipMessage& sub)
{

	h->setSubscriptionState(Active);
	h->send(h->accept());
    //PlainContents plain("test notify");
    //h->send(h->update(&plain));
	h->send(h->neutralNotify());

	subscribeServer_ = h.get();
	setResult(subscribeNew);
	fireResult(SipUserAgent::makeMsgBodyString(sub), SipUserAgent::makeMethodString(sub), SipUserAgent::makeStatusCode(sub));
}

void
SipUserAgent::SubscriptionHandler::onTerminated(ServerSubscriptionHandle)
{
	subscribeServer_ = NULL;
	setResult(subscribeTerminated);
	fireResult("Terminated", "NOTIFY", 200);
}
