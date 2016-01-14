
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SubscriptionHandler.hpp                                                   *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef SUBSCRIPTIONHANDLER_HPP_
#define SUBSCRIPTIONHANDLER_HPP_

#include "sip/resip_stack.h"
#include "sip/resip_dum.h"
#include "UserAgentCallbackImpl.hpp"

namespace SipUserAgent
{
	typedef enum
	{
		subscribeInit,
		subscribeNew,
		subscribeUpdatePending,
		subscribeUpdateActive,
		subscribeUpdateExtension,
		subscribeRequestRetry,
		subscribeTerminated,
	} SubscribeResult;

	typedef IUserAgentCallback<SubscribeResult> ISubscribeCallback;
	typedef std::vector<ISubscribeCallback*> SubscribeCallbackCollection;
	typedef SubscribeCallbackCollection::iterator SubscribeCallbackIterator;
	typedef UserAgentCallbackImpl<SubscribeCallbackCollection, SubscribeCallbackIterator, ISubscribeCallback, SubscribeResult>
			SubscribeCallbackImpl;

	class SubscriptionHandler : public SubscribeCallbackImpl,
								public resip::ClientSubscriptionHandler,
								public resip::ServerSubscriptionHandler
	{
	public:

		SubscriptionHandler() : SubscribeCallbackImpl(subscribeInit),
								subscribeServer_(NULL)
		{ }

		virtual ~SubscriptionHandler()
		{ }

		//Client must call acceptUpdate or rejectUpdate for any onUpdateFoo
		virtual void onUpdatePending(resip::ClientSubscriptionHandle h, const resip::SipMessage& notify, bool outOfOrder);
		virtual void onUpdateActive(resip::ClientSubscriptionHandle h, const resip::SipMessage& notify, bool outOfOrder);
		//unknown Subscription-State value
		virtual void onUpdateExtension(resip::ClientSubscriptionHandle h, const resip::SipMessage& notify, bool outOfOrder);

		virtual int onRequestRetry(resip::ClientSubscriptionHandle h, int retrySeconds, const resip::SipMessage& notify);

		//subscription can be ended through a notify or a failure response.
		virtual void onTerminated(resip::ClientSubscriptionHandle h, const resip::SipMessage* msg);
		//not sure if this has any value.
		virtual void onNewSubscription(resip::ClientSubscriptionHandle, const resip::SipMessage& notify);

		virtual void onNewSubscription(resip::ServerSubscriptionHandle, const resip::SipMessage& sub);
		virtual void onTerminated(resip::ServerSubscriptionHandle);

		// getters
		resip::ServerSubscription* getServerSubscription(void) const { return subscribeServer_; }

	protected:

		resip::ServerSubscription*	subscribeServer_;
	};

}


#endif /* SUBSCRIPTIONHANDLER_HPP_ */
