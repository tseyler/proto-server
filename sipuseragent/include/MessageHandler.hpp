
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* MessageHandler.hpp                                                   	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef MESSAGEHANDLER_HPP_
#define MESSAGEHANDLER_HPP_

#include "sip/resip_stack.h"
#include "sip/resip_dum.h"
#include "UserAgentCallbackImpl.hpp"

namespace SipUserAgent
{
	typedef enum
	{
		messageInit,
		messageSuccess,
		messageFailure,
		messageArrived,
	} MessageResult;

	typedef IUserAgentCallback<MessageResult> IMessageCallback;
	typedef std::vector<IMessageCallback*> MessageCallbackCollection;
	typedef MessageCallbackCollection::iterator MessageCallbackIterator;
	typedef UserAgentCallbackImpl<MessageCallbackCollection, MessageCallbackIterator, IMessageCallback, MessageResult>
			MessageCallbackImpl;

	class MessageHandler : 	public MessageCallbackImpl,
							public resip::ClientPagerMessageHandler,
							public resip::ServerPagerMessageHandler
	{
	public:

		MessageHandler() : MessageCallbackImpl(messageInit)
		{ }

	    virtual void onSuccess(resip::ClientPagerMessageHandle, const resip::SipMessage& status);
	    virtual void onFailure(resip::ClientPagerMessageHandle, const resip::SipMessage& status, std::auto_ptr<resip::Contents> contents);

	    virtual void onMessageArrived(resip::ServerPagerMessageHandle, const resip::SipMessage& message);
	};
}


#endif /* MESSAGEHANDLER_HPP_ */
