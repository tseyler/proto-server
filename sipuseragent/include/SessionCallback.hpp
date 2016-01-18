
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* SessionCallback.hpp                                            	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef SESSIONCALLBACK_HPP_
#define SESSIONCALLBACK_HPP_

#include "SessionDialog.hpp"

namespace SipUserAgent
{
	class ISessionCallback;
	typedef std::vector<ISessionCallback*> SessionCallbackCollection;
	typedef SessionCallbackCollection::iterator SessionCallbackIterator;

	typedef enum {
					sNewSession,
					sAnswer,
					sEarlyMedia,
					sOffer,
					sOfferRequired,
					sTerminated,
	} SessionStatus;

	class ISessionCallback
	{
	public:

		virtual void OnSessionChanged(SessionStatus ss, SessionDialog* dialog) = 0;

	};
}


#endif /* SESSIONCALLBACK_HPP_ */
