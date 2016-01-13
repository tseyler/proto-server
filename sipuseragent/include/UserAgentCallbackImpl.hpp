
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* UserAgentCallbackImpl.hpp                                            	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef USERAGENTCALLBACKIMPL_HPP_
#define USERAGENTCALLBACKIMPL_HPP_

#include <string>

#include "userAgentCallbackCollection.h"

namespace SipUserAgent
{
	template<class R>
	class IUserAgentCallback
	{
	public:

		virtual void OnResult(R result, const std::string& resultString,
										const std::string& methodString,
										int statusCode,
										const std::string& idString) = 0;
	};


	template<class C, class I, class O, class R>
	class UserAgentCallbackImpl
	{
	public:

		UserAgentCallbackImpl(R init) : result_(init)
		{}

	    // setters
		void		addCallback(O* callback)
		{
			addToCallbackCollection<C, O>(callbacks_, callback);
		}
		void		removeCallback(O* callback)
		{
			removeFromCallbackCollection<C, I, O>(callbacks_, callback);
		}
		void		setResult(R result) { result_ = result; }

		// getters
		R			getResult(void) const { return result_; }
		size_t		getCollectionSize(void) const { return callbacks_.size(); }
		void		fireResult(const std::string& response, const std::string& method, int statusCode, const std::string& id = "")
		{
			fireResultCallbacksCollection<C, I, O, R>(callbacks_, result_, response, method, statusCode, id);
		}

	protected:

	    R			result_;
	    C			callbacks_;
	};
}


#endif /* USERAGENTCALLBACKIMPL_HPP_ */
