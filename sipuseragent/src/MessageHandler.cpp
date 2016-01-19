
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* MessageHandler.cpp                                                   	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include "userAgentHelper.h"
#include "userAgentCallbackCollection.h"
#include "MessageHandler.hpp"

using namespace resip;

void
SipUserAgent::MessageHandler::onSuccess(ClientPagerMessageHandle, const SipMessage& status)
{
	setResult(messageSuccess);
	fireResult(SipUserAgent::makeResponseString(status), SipUserAgent::makeMethodString(status), SipUserAgent::makeStatusCode(status));
}

void
SipUserAgent::MessageHandler::onFailure(ClientPagerMessageHandle, const SipMessage& status, std::auto_ptr<Contents> /*contents*/)
{
	setResult(messageFailure);
	fireResult(SipUserAgent::makeResponseString(status), SipUserAgent::makeMethodString(status), SipUserAgent::makeStatusCode(status));
}

void
SipUserAgent::MessageHandler::onMessageArrived(ServerPagerMessageHandle, const SipMessage& message)
{
	setResult(messageArrived);
	fireResult(SipUserAgent::makeMsgBodyString(message), "MESSAGE", 200);
}

