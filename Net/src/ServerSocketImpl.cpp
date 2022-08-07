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
	if (mode & SELECT_ACCEPT)
		events |= POLLIN;
	if (mode & SELECT_ERROR)
		events |= POLLERR;
	return events;
}


short ServerSocketImpl::translateReadyEvents(short events, short interestMode) const
{
	short mode{};
	if (events & POLLIN && interestMode & SELECT_ACCEPT)
		mode |= SELECT_ACCEPT;
	if (events & POLLERR || (events & POLLHUP))
		mode |= SELECT_ERROR;
	return mode;
}


} } // namespace Poco::Net
