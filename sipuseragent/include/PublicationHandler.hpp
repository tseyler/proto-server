
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* PublicationHandler.hpp                                                    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef PUBLICATIONHANDLER_HPP_
#define PUBLICATIONHANDLER_HPP_

#include "sip/resip_dum.h"
#include "UserAgentCallbackImpl.hpp"

namespace SipUserAgent
{
	typedef enum
	{
		publishInit,
		publishSuccess,
		publishFailure,
		publishRemove,
		publishRequestRetry,
	} PublishResult;

	typedef IUserAgentCallback<PublishResult> IPublishCallback;
	typedef std::vector<IPublishCallback*> PublishCallbackCollection;
	typedef PublishCallbackCollection::iterator PublishCallbackIterator;
	typedef UserAgentCallbackImpl<PublishCallbackCollection, PublishCallbackIterator, IPublishCallback, PublishResult>
			PublishCallbackImpl;

	class PublicationHandler : 	public PublishCallbackImpl,
								public resip::ClientPublicationHandler
	{
	public:

		PublicationHandler() : 	PublishCallbackImpl(publishInit),
								publication_(NULL)
		{ }

		virtual ~PublicationHandler()
		{ }

		/// Called when the publication succeeds or each time it is sucessfully
		/// refreshed.
		virtual void onSuccess(resip::ClientPublicationHandle, const resip::SipMessage& status);

		//publication was successfully removed
		virtual void onRemove(resip::ClientPublicationHandle, const resip::SipMessage& status);

		//call on failure. The usage will be destroyed.  Note that this may not
		//necessarily be 4xx...a malformed 200, etc. could also reach here.
		virtual void onFailure(resip::ClientPublicationHandle, const resip::SipMessage& status);

		/// call on Retry-After failure.
		/// return values: -1 = fail, 0 = retry immediately, N = retry in N seconds
		virtual int onRequestRetry(resip::ClientPublicationHandle, int retrySeconds, const resip::SipMessage& status);

		// getters
		resip::ClientPublication*			getClientPublication(void) const { return publication_; }

	protected:

		resip::ClientPublication*			publication_;

	};
}



#endif /* PUBLICATIONHANDLER_HPP_ */
