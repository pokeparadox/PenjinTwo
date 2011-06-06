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
#include "Colour.h"
using Penjin::Colour;

void Colour::setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        toGL();
    #endif
}

void Colour::setOGLColour(CRfloat r, CRfloat g, CRfloat b, CRfloat a)
{
    #ifdef PENJIN_FIXED
        this->r = fixedpoint::fix2int(r);
        this->g = fixedpoint::fix2int(g);
        this->b = fixedpoint::fix2int(b);
        this->a = fixedpoint::fix2int(a);
    #else
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    #endif
    #if !defined (PENJIN_GL) && !defined (PENJIN_ES) && !defined (PENJIN_ES2)
        toNormal();
    #endif
}

void Colour::setColour(const COLOURS& c)
{
    if(c == RED)
	{
		r = 255;
		g = 0;
		b = 0;
	}
    else if(c == LIGHT_RED)
	{
		r = 255;
		g = 128;
		b = 128;
	}
	else if(c == GREEN)
	{
		r = 0;
		g = 255;
		b = 0;
	}
    else if(c == LIGHT_GREEN)
	{
		r = 128;
		g = 255;
		b = 128;
	}
	else if(c == BLUE)
	{
		r = 0;
		g = 0;
		b = 255;
	}
    else if(c == LIGHT_BLUE)
	{
		r = 128;
		g = 128;
		b = 255;
	}
	else if(c == YELLOW)
	{
		r = 255;
		g = 255;
		b = 0;
	}
	else if(c == WHITE)
	{
		r = 255;
		g = 255;
		b = 255;
	}
    else if(c == LIGHT_GREY)
	{
		r = 192;
		g = 192;
		b = 192;
	}
    else if(c == GREY)
	{
		r = 128;
		g = 128;
		b = 128;
	}
    else if(c == DARK_GREY)
	{
		r = 64;
		g = 64;
		b = 64;
	}
	else if(c == BLACK)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if(c == PURPLE)
	{
		r = 128;
		g = 0;
		b = 128;
	}
	else if(c == MAGENTA)
	{
		r = 255;
		g = 0;
		b = 255;
	}
	else if (c == CYAN)
	{
	    r = 0;
	    g = 255;
	    b = 255;
    }
	else if(c == ORANGE)
	{
		r = 255;
		g = 128;
		b = 0;
	}
	else if (c == BROWN)
	{
		r = 128;
		g = 64;
		b = 0;
	}
	a = 255;

    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        toGL();
    #endif
}

void Colour::setColour(CRint rgb)
{
    a = 255;
    r = (rgb & 0x0000ff);
    g = (rgb & 0x00ff00)/0x100;
    b = (rgb & 0xff0000)/0x10000;
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        toGL();
    #endif
}

bool Colour::lessThan(CRuchar r, CRuchar g, CRuchar b, CRuchar a)const
{
   if(this->r >= r)
      return false;
   if(this->g >= g)
      return false;
   if(this->b >= b)
      return false;
   if(this->a >= a)
      return false;
   return true;
}

bool Colour::isEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const
{
   if(this->r != r)
      return false;
   if(this->g != g)
      return false;
   if(this->b != b)
      return false;
   if(this->a != a)
      return false;
   return true;
}

SDL_Color Colour::getSDL_Colour()
{
    SDL_Color tempCol = {0,0,0,0};
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        tempCol.r = r * 255;
        tempCol.g = g * 255;
        tempCol.b = b * 255;
    #else
        tempCol.r = r;
        tempCol.g = g;
        tempCol.b = b;
	#endif
	return tempCol;
}

Uint32 Colour::getSDL_Uint32Colour(const SDL_Surface* dst)const{return SDL_MapRGBA(dst->format,r,g,b,a);}

void Colour::convertColour(Uint32 pixel,SDL_PixelFormat *format)
{

    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
        Uint8 r,g,b,a;
        SDL_GetRGBA(pixel,format,&r,&g,&b,&a);
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
        toGL();
    #else
        SDL_GetRGBA(pixel,format,&r,&g,&b,&a);
    #endif
}

#if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
    void Colour::toGL()
    {
        const float DIV_255 = 0.003921569f;
        r = r * DIV_255;
        g = g * DIV_255;
        b = b * DIV_255;
        a = a * DIV_255;
    }
    Colour Colour::getGreyScale()
    {
        float t = (r + g + b)*0.33f;
        return Colour(t,t,t);
    }
    void Colour::swapGB()
    {
        float t = g;
        g = b;
        b = t;
    }
    void Colour::swapRG()
    {
        float t = r;
        r = g;
        g = t;
    }
    void Colour::swapRB()
    {
        float t = r;
        r = b;
        b = t;
    }
#else
    void Colour::toNormal()
    {
        const uchar t = 255;
        r = r * t;
        g = g * t;
        b = b * t;
        a = a * t;
    }
    Colour Colour::getGreyScale()
    {
        uchar t = (r + g + b)*0.33f;
        return Colour(t,t,t);
    }
    void Colour::swapGB()
    {
        uchar t = g;
        g = b;
        b = t;
    }
    void Colour::swapRG()
    {
        uchar t = r;
        r = g;
        g = t;
    }
    void Colour::swapRB()
    {
        uchar t = r;
        r = b;
        b = t;
    }
#endif
