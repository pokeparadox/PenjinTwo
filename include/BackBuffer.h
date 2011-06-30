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
#ifndef BACKBUFFER_H
#define BACKBUFFER_H
#include "GFX.h"
#include "RenderObject.h"
#include "UpdateObject.h"
namespace Penjin
{
    class BackBuffer : public RenderObject, public UpdateObject
    {
        public:
            BackBuffer();
            virtual ~BackBuffer();

            void render();       // Render to the screen
            void update();      // Update from screen contents
            void setAlpha(CRuchar alpha){SDL_SetAlpha(buffer, SDL_SRCALPHA, alpha);}

        private:
            SDL_Surface* buffer;    //  The back buffer
    };
}


#endif // BACKBUFFER_H
