
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
*                                                                           *
* resip_stack_ssl.h                                                   		*
* Copyright (c) 2011, by Control4 Inc.  All rights reserved.	            *
* Created on: Sep 29, 2011													*
* Author: Terry Seyler														*
*                                                                           *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef RESIP_STACK_SSL_H_
#define RESIP_STACK_SSL_H_


//#if defined (USE_SSL)
#if defined(WIN32)
#include "resip/stack/ssl/WinSecurity.hxx"
#else
#include "resip/stack/ssl/Security.hxx"
#endif
//#endif

#endif /* RESIP_STACK_SSL_H_ */
