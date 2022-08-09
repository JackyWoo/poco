//
// ServerSocketImpl.cpp
//
// Library: Net
// Package: Sockets
// Module:  ServerSocketImpl
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/ServerSocketImpl.h"


namespace Poco {
namespace Net {


ServerSocketImpl::ServerSocketImpl()
{
}


ServerSocketImpl::~ServerSocketImpl()
{
}


short ServerSocketImpl::translateInterestMode(short mode) const
{
	short events{};
#if defined(POCO_HAVE_FD_EPOLL)
	if (mode & SELECT_ACCEPT)
		events |= EPOLLIN;
	if (mode & SELECT_ERROR)
		events |= EPOLLERR;
#elif defined(POCO_HAVE_FD_POLL)
	if (mode & SELECT_ACCEPT)
		events |= POLLIN;
	if (mode & SELECT_ERROR)
		events |= POLLERR;
#endif

	return events;
}


short ServerSocketImpl::translateReadyEvents(short events, short interestMode) const
{
	short mode{};
#if defined(POCO_HAVE_FD_EPOLL)
	if (events & EPOLLIN && interestMode & SELECT_ACCEPT)
		mode |= SELECT_ACCEPT;
	if (events & EPOLLERR || (events & EPOLLHUP))
		mode |= SELECT_ERROR;
#elif defined(POCO_HAVE_FD_POLL)
	if (events & POLLIN && interestMode & SELECT_ACCEPT)
		mode |= SELECT_ACCEPT;
	if (events & POLLERR || (events & POLLHUP))
		mode |= SELECT_ERROR;
#endif
	return mode;
}


} } // namespace Poco::Net
