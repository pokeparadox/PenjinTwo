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
*   \file CLASS_NAME is INSERT DESCRIPTION
*   \author Kevin Winfield-Pantoja
*/

#include "Surface.h"
using Penjin::Surface;

Surface::Surface() : surface(NULL)
{
    //ctor
}

Surface::~Surface()
{
    //dtor
}



Surface::Surface(const Surface& other)
{
    //copy ctor
}

Surface& Surface::operator=(const Surface& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

Penjin::ERRORS Surface::setSurface(SDL_Surface* s)
{
    surface = s;
    if(surface)
    {
        dimensions.x = surface->w;
        dimensions.y = surface->h;
    }
}

Penjin::ERRORS Surface::setSurface(Surface* s)
{
    surface = s->getSDL_Surface();
    if(surface)
    {
        dimensions.x = surface->w;
        dimensions.y = surface->h;
    }
    else
        return PENJIN_ERROR;
}

SDL_Surface* Surface::getSDL_Surface()
{
    return surface;
}

void Surface::render(Surface* s)
{
    if(s == NULL)
        return;

    if(surface)
    {
        //SDL_SetAlpha(surface, SDL_SRCALPHA, a);
        // Set up blitting area
        SDL_Rect src, dst;
        src.x = surface->clip_rect.x;
        src.y = surface->clip_rect.y;
        src.w = surface->w;
        src.h = surface->h;

        dst.x = position.x;
        dst.y = position.y;

        SDL_BlitSurface(surface, &src, s->getSDL_Surface(), &dst);
    }
}

void Surface::render()
{
    if(surface)
    {
        //SDL_SetAlpha(surface, SDL_SRCALPHA, a);
        // Set up blitting area
        SDL_Rect src, dst;
        src.x = surface->clip_rect.x;
        src.y = surface->clip_rect.y;
        src.w = surface->w;
        src.h = surface->h;

        dst.x = position.x;
        dst.y = position.y;

        SDL_BlitSurface(surface, &src, SDL_GetVideoSurface(), &dst);
    }
}

void Surface::clear()
{
    if(surface)
        SDL_FreeSurface(surface);
    surface = NULL;
}
