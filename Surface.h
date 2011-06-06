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
*   \file Surface is a class relating to storing pixels for blitting
*   \author Kevin Winfield-Pantoja
*/

/// NOTE: This class's intended purpose is to abstract from the SDL_Surface WIP
#ifndef SURFACE_H
#define SURFACE_H

#include "SDL/SDL.h"

namespace Penjin
{
    class Surface
    {
        public:
            /** Default constructor */
            Surface();
            /** Default destructor */
            virtual ~Surface();
            /** Copy constructor
             *  \param other Object to copy from
             */
            Surface(const Surface& other);
            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            Surface& operator=(const Surface& other);

            SDL_Surface* surface;
        protected:
        private:
    };
}
#endif // SURFACE_H
