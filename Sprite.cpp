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
#include "Sprite.h"
using Penjin::Sprite;

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

Penjin::ERRORS Sprite::setTransparentColour(const Colour& c)
{
    // We only have one image to set a transparent colour
    if(SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surface->format,c.r,c.g,c.b)) == -1)
        return PENJIN_SDL_INVALID_COLORKEY;
    return PENJIN_OK;
}

Penjin::ERRORS Sprite::setTransparentColour(const Vector2d<int>& v)
{
    return setTransparentColour( GFX::getInstance()->getPixel(v) );
}

void Sprite::disableTransparentColour()
{
    SDL_SetColorKey(surface, 0, surface->format->colorkey);
}

/*
Sprite::Sprite()
{

    position.x = 0;
    position.y = 0;
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif
    #ifdef PENJIN_SDL
        screen = GFX::getInstance()->getSDLVideoSurface();
    #endif
}
#ifndef PENJIN_3D
    Sprite::Sprite(CRint x,CRint y)
    {
        setPosition(x,y);
        #ifdef PENJIN_SDL
            screen = GFX::getInstance()->getSDLVideoSurface();
        #endif
    }
#else
    Sprite::Sprite(CRfloat x,CRfloat y)
    {
        setPosition(x,y);
    }
    Sprite::Sprite(CRfloat x,CRfloat y,CRfloat z)
    {
        setPosition(x,y,z);
    }
    Sprite::Sprite(const Vector3df& position)
    {
        setPosition(position);
    }
    Sprite::Sprite(const Vector2df& position)
    {
        setPosition(position);
    }
#endif

Penjin::ERRORS Sprite::loadSprite(CRstring fileName){return image.loadImage(fileName);}

#ifdef PENJIN_SDL
    void Sprite::render(SDL_Surface* screen){image.renderImage(screen,position);}
#else
    void Sprite::render(){image.renderImage(position);}
#endif

#ifdef PENJIN_SDL
}
#endif
*/

