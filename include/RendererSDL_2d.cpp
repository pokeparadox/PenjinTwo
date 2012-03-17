/*
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
*   \file RendererSDL_2d is a 2d renderer using SDL.
*   \author Kevin Winfield-Pantoja
*/
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "RendererSDL_2d.h"
#include "ErrorHandler.h"
#include "Surface.h"
#include "Rectangle.h"
#include "ConfigManager.h"

#ifdef PLATFORM_GP2X
    #include "MMUHack.h"
#elif PLATFORM_PANDORA
    #include <linux/fb.h>
    #include <sys/ioctl.h>
    #include <fcntl.h>
    #ifndef FBIO_WAITFORVSYNC
        #define FBIO_WAITFORVSYNC _IOW('F', 0x20, __u32)
    #endif
#endif
using Penjin::RendererSDL_2d;
using Penjin::ERRORS;
using Penjin::Surface;
using Penjin::Rectangle;
using Penjin::ConfigManager;


//RendererSDL_2d* RendererSDL_2d::instance = NULL;

RendererSDL_2d::RendererSDL_2d()
{
    //ctor
    ConfigMan::getInstance()->report("GFXSDL");
    ConfigMan::getInstance()->report("GFX2D");
}

RendererSDL_2d::~RendererSDL_2d()
{
    //dtor
}

/*RendererSDL_2d* RendererSDL_2d::getInstance()
{
    if( instance == NULL )
    {
        instance = new RendererSDL_2d;
    }
    return instance;
}*/

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
	    /// TODO: need to handle error here
		//PENJIN_SDL_VIDEO_QUERY_FAILED;
    }
    flags = SDL_SWSURFACE;// | SDL_DOUBLEBUF;

    if(fullScreen)
        flags= flags | SDL_FULLSCREEN;

    if(bpp == 0 || !(bpp == 8 || bpp == 16 || bpp == 32))
        bpp = info->vfmt->BitsPerPixel;

        screen = SDL_SetVideoMode(resolution.x, resolution.y, bpp, flags);
    if(screen  == NULL )
        ErrorMan::getInstance()->forceQuit(PENJIN_SDL_SETVIDEOMODE_FAILED);

    // We get the final resolution if  auto resolution has been set
    if(resolution.x == 0)
        resolution.x = screen->w;
    if(resolution.y == 0)
        resolution.y = screen->h;
}

void RendererSDL_2d::clear()
{
    SDL_FillRect(screen,NULL, clearColour.getSDL_Uint32Colour());
}

void RendererSDL_2d::blit()
{
    #ifdef PLATFORM_GP2X
        //  We do MMUHack BEFORE video flip!
        //if(useHack)
        MMUHack::flushCache(screen->pixels, (char*)screen->pixels  + (screen->w * screen->h));
    #elif PLATFORM_PANDORA
        //  vertical sync to prevent tearing
        int fd = open( "/dev/fb0" , O_RDONLY );
		if( 0 < fd )
		{
			int ret = 0;
			ret = ioctl(fd, FBIO_WAITFORVSYNC, &ret );
			/*if ( ret != 0 )
                VSYNC failed
			*/
		}
		close(fd);
    #endif
    SDL_Flip(screen);
}

Surface* RendererSDL_2d::scale(Surface* in, const float& s)
{
    Surface* out = NULL;
    out = new Surface;
    //  if the size is less than 1 we are shrinking
    if(s<1.0f)
    {
        int sFactor = 0;
        //  we convert some coom decimals to the integer fractions
        //  tenth of size
        if(s == 0.1f)
            sFactor = 10;
        else if(s == 0.16666666f)
            sFactor = 6;
        else if(s == 0.2f)
            sFactor = 5;
        //  quarter
        else if(s == 0.25f)
            sFactor = 4;
        else if(s == 0.33333333f)
            sFactor = 3;
        else if (s == 0.5f)
            sFactor = 2;
        out->setSurface(shrinkSurface(in->getSDL_Surface(),sFactor, sFactor));
    }
    else
        out->setSurface(zoomSurface(in->getSDL_Surface(),s,s,SMOOTHING_OFF));

    return out;
}

Surface* RendererSDL_2d::pokeScale(Surface* in, const int& s)
{
    // if nothing passed we can do nothing so return
    if(in == NULL)
        return in;

    // Create the output Surface
    Surface* out = NULL;
    out = scale(in, s);

    // Start at (0,0)
    Vector2d<int> px;

    // we work line by line
    for (px.y; px.y < in->getHeight(); ++px.y)
    {
        //we work along the current row
        while(px.x < in->getWidth())
        {
            Rectangle L = findLeftSlope(px, in);
            Rectangle R = findRightSlope(px, in);
            drawSlopes(L,R,s, out);
            if(R.getWidth() > 0)
                px.x = R.getPosition().x + R.getWidth();
            else
                ++px.x;

            if(px.x>= in->getWidth())
            {
                px.x = 0;
                break;
            }
        }
    }
    return out;
}

Rectangle RendererSDL_2d::findLeftSlope(const Vector2d<int>& start, Surface* in)
{
    //RendererSDL_2d* gfx = GFX::getInstance();
    Rectangle rect;
    rect.setPosition(start);
    rect.setDimensions(0,0);
    Colour sCol = getPixel(in,start);
    rect.setColour(sCol);

    // if we are at the extreme left or at the bottom, no slope!
    if(start.x == 0 || start.y >= getHeight()-1)
        return rect;
    //  Check if we have a slope in horizontal direction
    // If directly left is the same colour NO SLOPE
    if(sCol == getPixel(in, Vector2d<int>(start.x-1,start.y)))
        return rect;
    // Check the pixel down and left
    // if not the same colour then we have no near horizontal gradiant
    Vector2d<int> curr = start;
    --curr.x;
    ++curr.y;
    if(sCol == getPixel(in, curr))
    {
        // find the leftmost pixel with same colour
        for(curr.x; curr.x>=0; --curr.x)
        {
            if(sCol != getPixel(in, curr))
            {
                ++curr.x;
                rect.setPosition(curr);
                curr.y = curr.y-start.y;
                curr.x = start.x - curr.x;
                rect.setDimensions(curr);
                return rect;
            }
        }
    }
    /*
    /// THIS CODE IS BROKEN!
    // Check for a vertical slope instead
    // First check if there is a pixel immediately below of same colour
    curr = start;
    ++curr.y;
    if(sCol != gfx->getPixel(in, curr))
    {
        // Now we check every vertical pixel downwards and each time check to the left.
        for(curr.y; curr.y<gfx->getHeight(); ++curr.y)
        {
            // If there is a match we create the Rect
            if(sCol == gfx->getPixel(in, curr)
               && sCol == gfx->getPixel(in, Vector2d<int>(curr.x-1,curr.y) ))
            {
                --curr.x;
                rect.setPosition(curr);
                curr.y = curr.y-start.y;
                curr.x = start.x - curr.x;
                rect.setDimensions(curr);
                return rect;
            }
        }
    }*/
}

Rectangle RendererSDL_2d::findRightSlope(const Vector2d<int>& start, Surface* in)
{
    //RendererSDL_2d* gfx = GFX::getInstance();
    Rectangle rect;
    rect.setPosition(start);
    rect.setDimensions(0,0);
    Colour sCol = getPixel(in,start);
    rect.setColour(sCol);

    // if we are at the extreme right or at the bottom, no slope!
    if(start.x >= getWidth() || start.y >= getHeight()-1)
        return rect;
    //  Check if we have a slope in horizontal direction
    // If directly right is the same colour NO SLOPE
    if(sCol == getPixel(in, Vector2d<int>(start.x+1,start.y)))
        return rect;
    // Check the pixel down and right
    // if not the same colour then we have no near horizontal gradiant
    Vector2d<int> curr = start;
    ++curr.x;
    ++curr.y;
    if(sCol == getPixel(in, curr))
    {
        // find the leftmost pixel with same colour
        for(curr.x; curr.x<getWidth(); ++curr.x)
        {
            if(sCol != getPixel(in, curr))
            {
                --curr.x;
                rect.setPosition(start);
                rect.setDimensions(curr-start);
                return rect;
            }
        }
    }
    // Check for a vertical slope instead
    // First check if there is a pixel immediately below of same colour
    curr = start;
    ++curr.y;
    if(sCol != getPixel(in, curr))
    {
        // Now we check every vertical pixel downwards and each time check to the right.
        for(curr.y; curr.y<getHeight(); ++curr.y)
        {
            // If there is a match we create the Rect
            if(sCol == getPixel(in, curr)
               && sCol == getPixel(in, Vector2d<int>(curr.x+1,curr.y) ))
            {
                ++curr.x;
                rect.setPosition(start);
                rect.setDimensions(start-curr);
                return rect;
            }
        }
    }
}

void RendererSDL_2d::drawSlopes(const Rectangle& slopeL, const Rectangle& slopeR, const int& s, Surface* out)
{
    //RendererSDL_2d* gfx = GFX::getInstance();
    bool drawL = false;
    bool drawR = false;
    if(slopeL.getWidth()>0 && slopeL.getHeight()>0)
        drawL = true;
    if(slopeR.getWidth()>0 && slopeR.getHeight()>0)
        drawR = true;
    // drawLeft slope
    // And now we do the rendering on the large image.
    if(drawL)
    {
        Colour c = slopeL.getColour();
        Vector2d<int> pos = slopeL.getPosition();
        //pos.x--;
        pos.y--;
        filledTrigonRGBA(out->getSDL_Surface(),
        (pos.x + slopeL.getWidth())*s, pos.y*s,
        pos.x*s, (pos.y + slopeL.getHeight())*s,
        (pos.x + slopeL.getWidth())*s, (pos.y + slopeL.getHeight())*s,
        c.r, c.g, c.b, c.a);
    }

    // fill centre

    // draw right slope
    if(drawR)
    {
        Colour c = slopeR.getColour();
        Vector2d<int> pos = slopeR.getPosition();
        pos.x++;
        filledTrigonRGBA(out->getSDL_Surface(),
        pos.x*s, pos.y*s+1,
        pos.x*s, (pos.y + slopeR.getHeight())*s,
        (pos.x + slopeR.getWidth())*s-1,(pos.y + slopeR.getHeight())*s,
        c.r, c.g, c.b, c.a);
    }
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
    // Filled Rectangle
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
    if(s == NULL || pos.x >= s->w || pos.y >= s->h)
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

Penjin::Colour RendererSDL_2d::getPixel(Surface* s, Vector2d<int> pos)
{
    return getPixel(s->getSDL_Surface(), pos);
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

