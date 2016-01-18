
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* userAgentCallbackCollection.h                                             *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef USERAGENTCALLBACKCOLLECTION_H_
#define USERAGENTCALLBACKCOLLECTION_H_

#include <string>

namespace SipUserAgent
{
	template <class C, class B>
	void
	addToCallbackCollection(C& collection, B* callBack)
	{
		collection.push_back(callBack);
	}

	template <class C, class I, class B>
	void
	removeFromCallbackCollection(C& collection, B* callBack)
	{
		I it = collection.begin();

		while (it != collection.end())
		{
			B* cb = *it;
			if (cb == callBack) // we are the same callback
			{
				collection.erase(it);
				break;			// we're done
			}
			it++;
		}
	}

	template <class C, class I, class B, class R>
	void
	fireResultCallbacksCollection(C& collection, R resultCode, const std::string& resultString,
																const std::string& methodString, int statusCode, const std::string& id)
	{
		I it = collection.begin();

		while (it != collection.end())
		{
			B* cb = *it;
			cb->OnResult(resultCode, resultString, methodString, statusCode, id );
			it++;
		}
	}

}


#endif /* USERAGENTCALLBACKCOLLECTION_H_ */
