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
#include "Timer.h"
using Penjin::Timer;

#ifdef PENJIN_FIXED
Fixed Timer::calcScaler(const TimerScalers& mode)
#else
float Timer::calcScaler(const TimerScalers& mode)
#endif
{
    #ifdef PENJIN_FIXED
        Fixed divider;
        if (mode == FIFTEEN_FRAMES)
        {
            divider = 15;
            return (Fixed(MY_CLOCKS) / divider);
        }
        else if (mode == THIRTY_FRAMES)
        {
            divider = 30;
            return (Fixed(MY_CLOCKS) / divider);
        }
        else if (mode == FIFTY_FRAMES)
        {
            divider = 50;
            return (Fixed(MY_CLOCKS) / divider);
        }
        else if (mode == SIXTY_FRAMES)
        {
            divider = 60;
            return (Fixed(MY_CLOCKS) / divider);
        }
    #else
        if (mode == FIFTEEN_FRAMES)
            return ((float)MY_CLOCKS / 15.0f);
        else if (mode == THIRTY_FRAMES)
            return ((float)MY_CLOCKS / 30.0f);
        else if (mode == FIFTY_FRAMES)
            return ((float)MY_CLOCKS / 50.0f);
        else if (mode == SIXTY_FRAMES)
            return ((float)MY_CLOCKS / 60.0f);
    #endif
        else if (mode == MILLI_SECONDS)
            return (MY_CLOCKS / 1000);
        else if (mode == CENTI_SECONDS)
            return (MY_CLOCKS / 100);
        else if (mode == DECI_SECONDS)
            return (MY_CLOCKS / 10);
        else if (mode == SECONDS)
            return MY_CLOCKS;
        else if (mode == MINUTES)
            return (MY_CLOCKS * 60);
        else if (mode == HOURS)
            return (MY_CLOCKS * 60 * 60);
        else
            return MY_CLOCKS;
}

