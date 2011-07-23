/**
	\section LICENSE
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

	This file is part of PenjinTwo.

	PenjinTwo is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	PenjinTwo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with PenjinTwo.  If not, see <http://www.gnu.org/licenses/>.
*/
/***************************************************************************************************
*   \file Surface is a class relating to storing pixels for blitting
*   \author Kevin Winfield-Pantoja
*/

/// NOTE: This class's intended purpose is to abstract from the SDL_Surface WIP
#ifndef SURFACE_H
#define SURFACE_H

#include "SDL/SDL.h"
#include "RenderObject.h"
#include "DimensionObject.h"
#include "Brad.h"
#include "Errors.h"
namespace Penjin
{
    class Surface : public RenderObject, public DimensionObject
    {
        public:
            /** Default constructor */
            Surface();
            /** Default destructor */
            virtual ~Surface();

            Penjin::ERRORS setSurface(SDL_Surface* s);
            Penjin::ERRORS setSurface(Surface* s);

            /** Render to screen*/
            void render();

            /** Render to another Surface*/
            void render(Surface* s);

            void rotate(const float& degrees);
            void rotate(const Brad& brads);

            void scale(const float& scale);

            SDL_Surface* getSDL_Surface();

            /** Free the Surface */
            void clear();

        protected:
        private:
            /** Copy constructor
             *  \param other Object to copy from
             */
            Surface(const Surface& other);
            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            Surface& operator=(const Surface& other);

            // The RAW SDL_Surface* that we are abstracting from.
            SDL_Surface* surface;

            // We do no scaling to the RAW surface itself.
            virtual Vector2d<int> getScaledPosition(){return getPosition();}
            virtual Vector2d<int> getScaledDimensions(){return getDimensions();}

    };
}
#endif // SURFACE_H
