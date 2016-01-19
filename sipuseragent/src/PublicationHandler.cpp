
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* PublicationHandler.cpp                                                    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include "userAgentHelper.h"
#include "userAgentCallbackCollection.h"
#include "PublicationHandler.hpp"

using namespace resip;


void
SipUserAgent::PublicationHandler::onSuccess(ClientPublicationHandle h, const SipMessage& status)
{
	if (h.isValid())
		publication_ = h.get();

	setResult(publishSuccess);
	fireResult(SipUserAgent::makeResponseString(status), SipUserAgent::makeMethodString(status), SipUserAgent::makeStatusCode(status));
}

void
SipUserAgent::PublicationHandler::onRemove(ClientPublicationHandle, const SipMessage& status)
{
	publication_ = NULL;

	setResult(publishRemove);
	fireResult(SipUserAgent::makeResponseString(status), SipUserAgent::makeMethodString(status), SipUserAgent::makeStatusCode(status));
}

void
SipUserAgent::PublicationHandler::onFailure(ClientPublicationHandle, const SipMessage& status)
{
	publication_ = NULL;

	setResult(publishFailure);
	fireResult(SipUserAgent::makeResponseString(status), SipUserAgent::makeMethodString(status), SipUserAgent::makeStatusCode(status));
}

int
SipUserAgent::PublicationHandler::onRequestRetry(ClientPublicationHandle h, int retrySeconds, const SipMessage& status)
{
	if (h.isValid())
		publication_ = h.get();

	setResult(publishRequestRetry);
	fireResult(SipUserAgent::makeResponseString(status), SipUserAgent::makeMethodString(status), SipUserAgent::makeStatusCode(status));

	return retrySeconds;
}

