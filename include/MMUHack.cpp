/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "MMUHack.h"

#ifdef PLATFORM_GP2X

PenjinErrors::PENJIN_ERRORS MMUHack::init()
{
	system("/sbin/rmmod mmuhack");
	system("/sbin/insmod mmuhack.o");

	int mmufd = open("/dev/mmuhack", O_RDWR);
	if(mmufd < 0)
	{
		printf("MMU hack failed");
		return PenjinErrors::PENJIN_ERROR;
	}
	else
	{
		printf("MMU hack loaded");
		close(mmufd);
		return PenjinErrors::PENJIN_OK;
	}
	return PenjinErrors::PENJIN_ERROR;
}

void MMUHack::deInit()
{
	system("/sbin/rmmod mmuhack");
}


void MMUHack::flushCache(void *start_address, void *end_address)
{
	flush_uppermem_cache(start_address, end_address, 0);
}
#endif   // GP2X
