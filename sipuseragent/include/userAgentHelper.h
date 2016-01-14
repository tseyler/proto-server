
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* userAgentHelper.h                                                   	    *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef USERAGENTHELPER_H_
#define USERAGENTHELPER_H_

#ifndef WIN32
#include <syslog.h>
#endif
#include <stdarg.h>
#include "sip/resip_stack.h"
#include "sip/resip_dum.h"

namespace SipUserAgent
{
	// helper function
	bool 				isInteger(const std::string& val);

	const std::string 	CRLF = "\r\n";
	const std::string 	SPACE = " ";
	const std::string 	IP4 = "IN IP4";
	const std::string 	RTP = "RTP/AVP";

	std::string 		makeResponseString(const resip::SipMessage& response);
	std::string 		makeString(const resip::SipMessage& msg);
	std::string 		makeString(const resip::Data& data);
	resip::Data 		makeData(const std::string& strData);
	std::string 		makeMsgBodyString(const resip::SipMessage& msg);
	std::string 		makeMethodString(const resip::SipMessage& msg);
	int					makeStatusCode(const resip::SipMessage& msg);
	std::string			makeAor(const resip::Uri& uri);
	std::string 		makeUser(const resip::Uri& uri);
	std::string 		makeHost(const resip::Uri& uri);
	resip::NameAddr		makeNameAddr(const std::string& contact);
	// parseRtpMapAttribute returns the key
	int					parseRtpMapAttribute(const std::string& value);

	// logging
	void				openUALog(const std::string& ident);
	void				closeUALog(void);

//#define	LOG_EMERG	0	/* system is unusable */
//#define	LOG_ALERT	1	/* action must be taken immediately */
//#define	LOG_CRIT	2	/* critical conditions */
//#define	LOG_ERR		3	/* error conditions */
//#define	LOG_WARNING	4	/* warning conditions */
//#define	LOG_NOTICE	5	/* normal but significant condition */
//#define	LOG_INFO	6	/* informational */
//#define	LOG_DEBUG	7	/* debug-level messages */

	// one of the above logLevels
	void				logUA(int logLevel, const char* fmt, ...);

	void				logInfoUA(const char* fmt, ...);
	void				logErrorUA(const char* fmt, ...);
	void				logDebugUA(const char* fmt, ...);
	void				logWarningUA(const char* fmt, ...);

	void				logInfoUA(const std::string& func, const std::string& logMsg);
	void				logWarningUA(const std::string& func, const std::string& logMsg);
	void				logDebugUA(const std::string& func, const std::string& logMsg);
	void				logErrorUA(const std::string& func, const std::string& logMsg,
																	const std::string& file, int line);

#define	STD_STRING( s )								std::string(s)

#define LOG_UA_INFO( func, msg )					SipUserAgent::logInfoUA(func, msg)
#define LOG_UA_ERROR( func, msg, file, line )		SipUserAgent::logErrorUA(func, msg, file, line)
#define LOG_UA_WARNING( func, msg )					SipUserAgent::logWarningUA(func, msg)
#define LOG_UA_DEBUG( func, msg )					SipUserAgent::logDebugUA(func, msg)


// The template collection functions below are for vector based collections

	template <class C, class O>
	void
	addToCollection(C& coll, O obj)
	{
		coll.push_back(obj);
	}

	template <class C, class I, class O>
	void
	removeFromCollection(C& coll, O obj)
	{
		I it = coll.begin();

		while (it != coll.end())
		{
			O o = *it;
			if (o == obj)
			{
				coll.erase(it);
				break;			// we're done
			}
			it++;
		}
	}

	template <class C>
	void						// this will call the destructor on all elements of the collection
	emptyCollection(C& coll)
	{
		coll.erase(coll.begin(), coll.end());
	}

	template <class C, class I, class O>
	void
	catCollection(C& srcColl, C& destColl)
	{
		I it = srcColl.begin();

		while (it != srcColl.end())
		{
			O o = *it;
			addToCollection<C, O>(destColl, o);
			it++;
		}
	}

	template <class C>
	void
	copyCollection(C& srcColl, C& destColl)
	{
		destColl = srcColl;	// does a copy
	}

	template <class C, class O>
	O
	getFromCollection(C& coll, size_t idx, O obj)
	{
		return (!coll.empty() && idx < coll.size()) ? coll.at(idx) : obj;
	}

	template <class C, class I, class O>
	I 							// return an iterator from a matching object or end() if no match
	getIteratorFromCollection(C& coll, O obj)
	{
		I it = coll.begin();

		while (it != coll.end())
		{
			O o = *it;
			if (o == obj)
				break;			// we're done
			it++;
		}

		return it;
	}

	template <class C, class O>
	O
	getFrontFromCollection(C& coll, O obj)
	{
		return (!coll.empty()) ? coll.front() : obj;
	}

	template <class C, class O>
	O
	getBackFromCollection(C& coll, O obj)
	{
		return (!coll.empty()) ? coll.back() : obj;
	}

	// this assumes the collection has unique data members
	template <class C, class I, class O>
	O
	getNextFromCollection(C& coll, O obj)
	{
		I it = getIteratorFromCollection<C, I, O>(coll, obj);

		return (++it != coll.end()) ? *it : obj;
	}


}


#endif /* USERAGENTHELPER_H_ */
