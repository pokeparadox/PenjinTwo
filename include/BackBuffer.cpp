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
#include "BackBuffer.h"
#include "Surface.h"
using Penjin::BackBuffer;
using Penjin::Surface;

#ifdef PENJIN_SDL
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
        SDL_Rect src, dst;
        src.x = buffer->clip_rect.x;
        src.y = buffer->clip_rect.y;
        src.w = buffer->w;
        src.h = buffer->h;
        Renderer* gfx = GFX;
        if(gfx->getScaleMode() == smNONE)
        {
            dst.x = position.x;
            dst.y = position.y;
        }
        else
        {
            dst.x = getScaledPosition().x;
            dst.y = getScaledPosition().y;
        }
        SDL_BlitSurface(buffer, &src, GFX_SDL_2D::getInstance()->getSDLVideoSurface(), &dst);
    }

    void BackBuffer::update()
    {
        SDL_Surface* scr = SDL_GetVideoSurface();
        if(buffer == NULL)
            buffer = SDL_CreateRGBSurface(scr->flags,scr->w, scr->h, scr->format->BitsPerPixel, 0, 0, 0, 0);
        SDL_BlitSurface(scr, NULL, buffer, NULL);
    }

    void BackBuffer::scale(const float& s)
    {
        Renderer* gfx = GFX;
        Surface* newSurf = NULL;
        newSurf = new Surface();
        newSurf->setSurface(buffer);
        newSurf = gfx->scale(newSurf,s);
        if(newSurf && newSurf->getSDL_Surface())
        {
            SDL_FreeSurface(buffer);
            buffer = newSurf->getSDL_Surface();
        }
        delete newSurf;
    }
#elif PENJIN_GL
    BackBuffer::BackBuffer()
    {
        //ctor
    }

    BackBuffer::~BackBuffer()
    {
        //dtor
    }


    void BackBuffer::render()
    {/*
        SDL_Rect src, dst;
        src.x = buffer->clip_rect.x;
        src.y = buffer->clip_rect.y;
        src.w = buffer->w;
        src.h = buffer->h;
        Renderer* gfx = GFX::getInstance();
        if(gfx->getScaleMode() == smNONE)
        {
            dst.x = position.x;
            dst.y = position.y;
        }
        else
        {
            dst.x = getScaledPosition().x;
            dst.y = getScaledPosition().y;
        }
        SDL_BlitSurface(buffer, &src, GFX::getInstance()->getSDLVideoSurface(), &dst);
        */
    }

    void BackBuffer::update()
    {
        /*
        SDL_Surface* scr = SDL_GetVideoSurface();
        if(buffer == NULL)
            buffer = SDL_CreateRGBSurface(scr->flags,scr->w, scr->h, scr->format->BitsPerPixel, 0, 0, 0, 0);
        SDL_BlitSurface(scr, NULL, buffer, NULL);
        */
    }

    void BackBuffer::scale(const float& s)
    {
        /*
        Renderer* gfx = GFX::getInstance();
        Surface* newSurf = NULL;
        newSurf = new Surface();
        newSurf->setSurface(buffer);
        newSurf = gfx->scale(newSurf,s);
        if(newSurf && newSurf->getSDL_Surface())
        {
            SDL_FreeSurface(buffer);
            buffer = newSurf->getSDL_Surface();
        }
        delete newSurf;*/
    }
#endif
