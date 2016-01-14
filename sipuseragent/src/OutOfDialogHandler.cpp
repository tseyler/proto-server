
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* OutOfDialogHandler.cpp                                                    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include "userAgentHelper.h"
#include "userAgentCallbackCollection.h"
#include "OutOfDialogHandler.hpp"

using namespace resip;

void
SipUserAgent::OutOfDialogHandler::onSuccess(ClientOutOfDialogReqHandle, const SipMessage& response)
{
	setResult(oodSuccess);
	fireResult(SipUserAgent::makeResponseString(response), SipUserAgent::makeMethodString(response), SipUserAgent::makeStatusCode(response));
}

void
SipUserAgent::OutOfDialogHandler::onFailure(ClientOutOfDialogReqHandle, const SipMessage& response)
{
	setResult(oodFailure);
	fireResult(SipUserAgent::makeResponseString(response), SipUserAgent::makeMethodString(response), SipUserAgent::makeStatusCode(response));

}

void
SipUserAgent::OutOfDialogHandler::onReceivedRequest(ServerOutOfDialogReqHandle ood, const SipMessage& request)
{
	if (ood.isValid())
		ood->send(ood->answerOptions());
	setResult(oodRecvRequest);
	fireResult(SipUserAgent::makeResponseString(request), SipUserAgent::makeMethodString(request), SipUserAgent::makeStatusCode(request));
}


