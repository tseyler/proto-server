
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* RegistrationHandler.cpp                                                   *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <sstream>

#include "userAgentHelper.h"
#include "userAgentCallbackCollection.h"
#include "RegistrationHandler.hpp"

using namespace resip;

void
SipUserAgent::RegistrationHandler::onSuccess(ClientRegistrationHandle h, const SipMessage& response)
{
	if (h.isValid())
		registration_ = h.get();
	registered_ = true;

	setResult(regSuccess);
	fireResult(SipUserAgent::makeResponseString(response), SipUserAgent::makeMethodString(response),
			SipUserAgent::makeStatusCode(response));
	LOG_UA_INFO( STD_STRING( "RegistrationHandler::onSuccess" ), SipUserAgent::makeResponseString(response) );
}

void
SipUserAgent::RegistrationHandler::onRemoved(ClientRegistrationHandle, const SipMessage& response)
{
	setResult(regRemoved);
	fireResult(SipUserAgent::makeResponseString(response), SipUserAgent::makeMethodString(response),
			SipUserAgent::makeStatusCode(response));
	LOG_UA_INFO( STD_STRING( "RegistrationHandler::onRemoved" ), SipUserAgent::makeResponseString(response) );

	resetRegistration();
}

void
SipUserAgent::RegistrationHandler::onFailure(ClientRegistrationHandle, const SipMessage& response)
{
	registration_ = NULL;
	registered_ = false;

	setResult(regFailure);
	fireResult(SipUserAgent::makeResponseString(response), SipUserAgent::makeMethodString(response),
			SipUserAgent::makeStatusCode(response));
	LOG_UA_WARNING(  STD_STRING( "RegistrationHandler::onFailure" ), SipUserAgent::makeResponseString(response) );
}

int
SipUserAgent::RegistrationHandler::onRequestRetry(ClientRegistrationHandle, int retry, const SipMessage& response)
{
	registration_ = NULL;
	registered_ = false;

	setResult(regRetry);
	fireResult(SipUserAgent::makeResponseString(response), SipUserAgent::makeMethodString(response),
			SipUserAgent::makeStatusCode(response));
	LOG_UA_WARNING(  STD_STRING( "RegistrationHandler::onRequestRetry" ), SipUserAgent::makeResponseString(response) );

	switch (retry)
	{
		case -1:

			LOG_UA_ERROR( STD_STRING( "RegistrationHandler::onRequestRetry" ),
				STD_STRING( "Failure with on request retry" ), STD_STRING( __FILE__ ), __LINE__ );
			break;
		case 0:	// override with our own retry in seconds

			retry = regRetrySec_;
			break;
	}

	return retry;
}

void
SipUserAgent::RegistrationHandler::unRegister(void)
{
	if (registration_ && registered_)
	{
		// Remove all registrations associated with this AOR.
		registration_->removeAll(true);
		LOG_UA_INFO( STD_STRING( "RegistrationHandler::unRegister" ), STD_STRING( "Useragent has been unregistered") );
	}
}

void
SipUserAgent::RegistrationHandler::stopRegistering(void)
{
	if (registration_ && registered_)
	{
		registration_->stopRegistering();
		LOG_UA_INFO( STD_STRING( "RegistrationHandler::stopRegistering" ), STD_STRING( "Useragent is no longer being registered") );
	}
}

void
SipUserAgent::RegistrationHandler::resetRegistration(void)
{
	setResult(regInit);
	registration_ = NULL;
	registered_ = false;
}




