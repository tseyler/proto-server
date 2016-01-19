
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* userAgentHelper.cpp                                                       *
* Author: Terry Seyler							    *
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <stdio.h>
#include <sstream>
#include <istream>
#include <stdlib.h>
#include "userAgentHelper.h"

bool
SipUserAgent::isInteger(const std::string& val)
{
	std::istringstream iss(val);

	int sink;
	iss >> sink;

	return ( iss.rdbuf()->in_avail() == 0 );
}

std::string
SipUserAgent::makeResponseString(const resip::SipMessage& response)
{
	return response.isResponse() ? makeString(response) : std::string("Invalid Response");
}

std::string
SipUserAgent::makeString(const resip::SipMessage& msg)
{
	std::stringstream ss;
	ss << msg.brief();

	return ss.str();
}

std::string
SipUserAgent::makeString(const resip::Data& data)
{
	std::stringstream ss;
	ss << data;

	return ss.str();
}

resip::Data
SipUserAgent::makeData(const std::string& strData)
{
	return resip::Data(strData.c_str());
}

std::string
SipUserAgent::makeMsgBodyString(const resip::SipMessage& msg)
{
	return (msg.getContents()) ? makeString(msg.getContents()->getBodyData()) : "";
}

std::string
SipUserAgent::makeMethodString(const resip::SipMessage& response)
{
	if (response.isResponse())
		 SipUserAgent::makeString(response.methodStr());

	return "";
}

int
SipUserAgent::makeStatusCode(const resip::SipMessage& response)
{
	if (response.isResponse())
	{
		resip::StatusLine status = response.header(resip::h_StatusLine);
		return status.statusCode();
	}

	return -1; // status codes will never be negative
}

std::string
SipUserAgent::makeAor(const resip::Uri& uri)
{
	return SipUserAgent::makeString(uri.getAorNoPort());
}

std::string
SipUserAgent::makeUser(const resip::Uri& uri)
{
	return SipUserAgent::makeString(uri.user());
}

std::string
SipUserAgent::makeHost(const resip::Uri& uri)
{
	return SipUserAgent::makeString(uri.host());
}

resip::NameAddr
SipUserAgent::makeNameAddr(const std::string& contact)
{
	return resip::NameAddr(contact.c_str());
}

int
SipUserAgent::parseRtpMapAttribute(const std::string& value)
{
	size_t p0 = 0, p1 = std::string::npos;
	std::string val("");
	while (p0 != std::string::npos)
	{
		p1 = value.find_first_of(" ", p0);
		if (p1 != p0)	// not the same position
		{
			val = value.substr(p0, p1 - p0);
			return (isInteger(val)) ? atoi(val.c_str()) : -1;
		}
	}

	return -1;
}

void
SipUserAgent::openUALog(const std::string& ident)
{
#ifndef WIN32
	openlog(ident.c_str(), LOG_PID|LOG_CONS, LOG_USER);
#endif
}

void
SipUserAgent::closeUALog(void)
{
#ifndef WIN32
	closelog();
#endif
}

void
SipUserAgent::logUA(int logLevel, const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
#ifdef WIN32
	vprintf(fmt, ap);
	printf("\n");
#else
	vsyslog(logLevel, fmt, ap);
#endif
	va_end(ap);
}

void
SipUserAgent::logInfoUA(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
#ifdef WIN32
	vprintf(fmt, ap);
	printf("\n");
#else
	vsyslog(LOG_INFO, fmt, ap);
#endif
	va_end(ap);
}

void
SipUserAgent::logErrorUA(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
#ifdef WIN32
	vprintf(fmt, ap);
	printf("\n");
#else
	vsyslog(LOG_ERR, fmt, ap);
#endif
	va_end(ap);
}

void
SipUserAgent::logDebugUA(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
#ifdef WIN32
	vprintf(fmt, ap);
	printf("\n");
#else
	vsyslog(LOG_DEBUG, fmt, ap);
#endif
	va_end(ap);
}

void
SipUserAgent::logWarningUA(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
#ifdef WIN32
	vprintf(fmt, ap);
	printf("\n");
#else
	vsyslog(LOG_WARNING, fmt, ap);
#endif
	va_end(ap);
}

void
SipUserAgent::logInfoUA(const std::string& func, const std::string& logMsg)
{
	std::stringstream ss;
	ss << "SipUserAgent::INFO From-> " << func << " Message-> " << logMsg;
	logInfoUA(ss.str().c_str());
}

void
SipUserAgent::logWarningUA(const std::string& func, const std::string& logMsg)
{
	std::stringstream ss;
	ss << "SipUserAgent::WARNING From-> " << func << " Message-> " << logMsg;
	logWarningUA(ss.str().c_str());
}

void
SipUserAgent::logErrorUA(const std::string& func, const std::string& logMsg, const std::string& file, int line)
{
	std::stringstream ss;
	ss << "SipUserAgent::ERROR From-> " << func << " Message-> " << logMsg << " | File: " << file << " | Line: " << line;
	logErrorUA(ss.str().c_str());
}

void
SipUserAgent::logDebugUA(const std::string& func, const std::string& logMsg)
{
	std::stringstream ss;
	ss << "SipUserAgent::ERROR From-> " << func << " Message-> " << logMsg;
	logErrorUA(ss.str().c_str());
}
