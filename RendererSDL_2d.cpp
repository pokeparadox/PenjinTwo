/*
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
*   \file RendererSDL_2d is a 2d renderer using SDL.
*   \author Kevin Winfield-Pantoja
*/
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "RendererSDL_2d.h"
#include "Errors.h"
using Penjin::RendererSDL_2d;
using Penjin::ERRORS;

RendererSDL_2d::RendererSDL_2d()
{
    //ctor
}

RendererSDL_2d::~RendererSDL_2d()
{
    //dtor
}


void RendererSDL_2d::showCursor(const bool & show)
{
    if(show)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void RendererSDL_2d::applyVideoSettings()
{
    const SDL_VideoInfo* info = NULL;	//Information about the current video settings
    int flags = 0;						//Flags for SDL_SetVideoMode
    //Get some video information
    info = SDL_GetVideoInfo();
    if(!info)
	{
	    //need to handle error here
		//PENJIN_SDL_VIDEO_QUERY_FAILED;
    }
    flags = SDL_SWSURFACE | SDL_DOUBLEBUF;

    if(fullScreen)
        flags= flags | SDL_FULLSCREEN;

    if(bpp == 0 || !(bpp == 8 || bpp == 16 || bpp == 32))
        bpp = info->vfmt->BitsPerPixel;

        screen = SDL_SetVideoMode(dimensions.x, dimensions.y, bpp, flags);
    if(screen  == NULL )
        PENJIN_SDL_SETVIDEOMODE_FAILED;
}

void RendererSDL_2d::clear()
{
    SDL_FillRect(screen,NULL, clearColour.getSDL_Uint32Colour());
}

void RendererSDL_2d::blit()
{
    SDL_Flip(screen);
}

void RendererSDL_2d::drawPixel(const Vector2d<float> & v)
{
        SDL_Rect r;
        int t = drawWidth*0.5f;
        r.x=v.x-t;
        r.y=v.y-t;
        r.w=r.h=drawWidth;
        SDL_FillRect(screen,&r,drawColour.getSDL_Uint32Colour());
}

// Deprecated... we need more functions that don't expose the SDL inner workings.
void RendererSDL_2d::drawPixel(SDL_Surface* s, const Vector2d<float> & v)
{
        SDL_Rect r;
        int t = drawWidth*0.5f;
        r.x=v.x-t;
        r.y=v.y-t;
        r.w=r.h=drawWidth;
        SDL_FillRect(s,&r,drawColour.getSDL_Uint32Colour());
}

void RendererSDL_2d::drawLine(const Vector2d<float> & p1, const Vector2d<float> & p2)
{
    /*
    // When source changes have filtered through this function will be useful...
    thickLineRGBA(screen,
    p1.x, p1.y,
    p2.x, p2.y,
    drawWidth,
    drawColour.red, drawColour.green, drawColour.blue, drawColour.alpha);
    */
    lineRGBA(screen,
    p1.x, p1.y,
    p2.x, p2.y,
    drawColour.r, drawColour.g, drawColour.b, drawColour.a);
}

void RendererSDL_2d::drawRectangle(const Vector2d<float> & pos, const Vector2d<int> & dims)
{
    if(drawWidth<=0)
        boxRGBA(screen, pos.x, pos.y, pos.x+ dims.x, pos.y+ dims.y, drawColour.r, drawColour.g, drawColour.b, drawColour.a);
    else
    {
        //  TODO: variable width support.
        rectangleRGBA(screen, pos.x, pos.y, pos.x+ dims.x, pos.y+ dims.y, drawColour.r, drawColour.g, drawColour.b, drawColour.a);
    }
}

void RendererSDL_2d::drawEllipse(const Vector2d<float> & centre, const float& rx, const float& ry)
{
    if(drawWidth<=0)
        filledEllipseRGBA(screen, centre.x, centre.y, rx, ry, drawColour.r, drawColour.g, drawColour.b, drawColour.a);
    else
    {
        //  TODO: variable width support.
        ellipseRGBA(screen, centre.x, centre.y, rx, ry, drawColour.r, drawColour.g, drawColour.b, drawColour.a);
    }
}

Penjin::Colour RendererSDL_2d::getPixel(Vector2d<int> pos)
{
    return getPixel(screen,pos);
}

Penjin::Colour RendererSDL_2d::getPixel(SDL_Surface* s, Vector2d<int> pos)
{
    if(s == NULL)
        return Colour(MAGENTA);
    int bpp = s->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)s->pixels + pos.y * s->pitch + pos.x * bpp;
    Colour c;
    switch(bpp) {
    case 1:
        c.convertColour(*p,s->format);break;

    case 2:
        c.convertColour(*(Uint16 *)p,s->format);break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            c.convertColour(p[0] << 16 | p[1] << 8 | p[2],s->format);
        else
            c.convertColour(p[0] | p[1] << 8 | p[2] << 16,s->format);
        break;
    case 4:
        c.convertColour( *(Uint32 *)p,s->format);break;

    default:
        c.setColour(MAGENTA);       /* shouldn't happen, but avoids warnings */
    }
    return c;
}

Penjin::Colour RendererSDL_2d::getPixel(Surface s, Vector2d<int> pos)
{
    return getPixel(s.surface, pos);
}

void RendererSDL_2d::showVideoInfo()
{

}

// Deprecated
SDL_Surface* RendererSDL_2d::getSDLVideoSurface()
{
    return screen;
}

SDL_Surface* RendererSDL_2d::cropSurface(SDL_Surface* in, SDL_Rect* c)
{
    SDL_Surface *cropped = NULL;
    //  Cropped surface
    cropped = SDL_CreateRGBSurface(in->flags,c->w, c->h,in->format->BitsPerPixel, 0, 0, 0, 0);
    Colour col = getPixel(cropped,Vector2d<int>(0,0));
    SDL_SetColorKey(cropped, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(cropped->format,col.r,col.g,col.b));
    SDL_BlitSurface(in,c,cropped,NULL);
    return cropped;
}

void RendererSDL_2d::lockSurface(SDL_Surface* s)
{
        // Check and lock the surface if necessary.
        if (SDL_MUSTLOCK(s))
            SDL_LockSurface(s);
}

void RendererSDL_2d::unlockSurface(SDL_Surface* s)
{
        // Check and unlock the surface if necessary
        if ( SDL_MUSTLOCK(s) )
            SDL_UnlockSurface(s);
}

