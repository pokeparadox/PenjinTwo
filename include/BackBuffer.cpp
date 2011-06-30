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
#include "BackBuffer.h"
using Penjin::BackBuffer;

BackBuffer::BackBuffer() : buffer(NULL)
{
    //ctor
}

BackBuffer::~BackBuffer()
{
    //dtor
    if(buffer)
        SDL_FreeSurface(buffer);
    buffer = NULL;
}


    void BackBuffer::render()
    {
        SDL_BlitSurface(buffer, NULL, SDL_GetVideoSurface(), NULL);
    }

    void BackBuffer::update()
    {
        SDL_Surface* scr = SDL_GetVideoSurface();
        if(buffer == NULL)
            buffer = SDL_CreateRGBSurface(scr->flags,scr->w, scr->h, scr->format->BitsPerPixel, 0, 0, 0, 0);
        SDL_BlitSurface(scr, NULL, buffer, NULL);
    }

