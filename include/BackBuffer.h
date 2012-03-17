/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

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

            /** \brief Render the contents of the BackBuffer to the screen*/
            void render();
            /** \brief copy the screen into the BackBuffer*/
            void update();

            /** \brief Set the alpha value of the surface
                \param alpha : The value used for transparency (0-255) where 0 is completely transparent.*/
            void setAlpha(const unsigned char& alpha)
            {
                #ifdef PENJIN_SDL
                SDL_SetAlpha(buffer, SDL_SRCALPHA, alpha);
                #elif PENJIN_GL
                this->alpha = alpha * 0.003921569f;
                #endif
            }

            void scale(const float & s);

        private:
            #ifdef PENJIN_SDL
            SDL_Surface* buffer;    //  The back buffer
            #elif PENJIN_GL
            float alpha;
            #endif
    };
}


#endif // BACKBUFFER_H
