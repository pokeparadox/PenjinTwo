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
*   \file StateExample is the ErrorState of Penjin shown if there is a mistake with your state code.
*   \author Kevin Winfield-Pantoja
*/

#ifndef STATEEXAMPLE_H
#define STATEEXAMPLE_H

#include "ApplicationState.h"

namespace Penjin
{
    class StateExample : public ApplicationState
    {
        public:
            /** Default constructor */
            StateExample();
            /** Default destructor */
            virtual ~StateExample();

            virtual void render();
            virtual void update();
            virtual void input();

    };
}
#endif // STATEEXAMPLE_H
