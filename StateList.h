#ifndef STATELIST_H_INCLUDED
#define STATELIST_H_INCLUDED

/**
	\section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
/***************************************************************************************************
*   \file StateList is template file of Penjin to demonstrate state lists.
*   \author Kevin Winfield-Pantoja
*/

/*
Here you include the header of each state you create
*/
#include "StateExample.h"
//  Local file per project wi just a list of each state .h file
#include "MyStateIncludes.h"

namespace Penjin
{
    /*
        You add your state identifier in the enum below
    */
    enum STATES
    {
        STATE_EXAMPLE= -1,  // An example state just to show how to do states
        STATE_NULL = 0,
        //  Add your own state identifiers below in the local per-project file
        #include "MyStateList.h"
    };
}
#endif // STATELIST_H_INCLUDED
