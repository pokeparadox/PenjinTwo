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
#ifndef MMUHACK_H
#define MMUHACK_H

#ifdef PLATFORM_GP2X
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/mman.h>


#include "mmuhack/flush_uppermem_cache.h"
#include "PenjinErrors.h"


namespace MMUHack
{
        PenjinErrors::PENJIN_ERRORS init();	//	Startup the MMU Hack. should be done after any dispay initialisation
        void deInit();	//	Shutdown the MMU Hack. performed before program shutdown

        //	Flush cache clears cache and should be called immediately before you blit the screen
        //e.g. fr SDL:  hack.flushCache(screen->pixels, screen->pixels + 76800)//320*240 = 76800
        void flushCache(void *start_address, void *end_address);
}
#endif   // GP2X
#endif	//	MMUHACK_H

