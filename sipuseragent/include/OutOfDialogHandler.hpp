
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* OutOfDialogHandler.hpp                                                    *
* Author: Terry Seyler				      			    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef OUTOFDIALOGHANDLER_HPP_
#define OUTOFDIALOGHANDLER_HPP_

#include <string>
#include <vector>
#include "sip/resip_dum.h"
#include "UserAgentCallbackImpl.hpp"

namespace SipUserAgent
{
	typedef enum
	{
		oodInit,
		oodSuccess,
		oodFailure,
		oodRecvRequest,
	} OodResult;

	typedef IUserAgentCallback<OodResult> IOutOfDialogCallback;
	typedef std::vector<IOutOfDialogCallback*> OodCallbackCollection;
	typedef OodCallbackCollection::iterator OodCallbackIterator;
	typedef UserAgentCallbackImpl<OodCallbackCollection, OodCallbackIterator, IOutOfDialogCallback, OodResult>
			OodCallbackImpl;

	class OutOfDialogHandler : 	public OodCallbackImpl,
								public resip::OutOfDialogHandler
	{
	public:

		OutOfDialogHandler() : OodCallbackImpl(oodInit)
		{}

		virtual ~OutOfDialogHandler()
		{}

		virtual void onSuccess(resip::ClientOutOfDialogReqHandle, const resip::SipMessage& successResponse);
	    virtual void onFailure(resip::ClientOutOfDialogReqHandle, const resip::SipMessage& errorResponse);
	    virtual void onReceivedRequest(resip::ServerOutOfDialogReqHandle ood, const resip::SipMessage& request);
	};

}


#endif /* OUTOFDIALOGHANDLER_HPP_ */
