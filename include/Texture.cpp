/**
	\section LICENSE
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
*   \file Texture is a class to handle the storage of hardware accelerated  images normally stored in GFX RAM
*   \author Kevin Winfield-Pantoja
*/

#if PENJIN_GL
    #include <SDL/SDL_opengl.h>
#endif

#include "Texture.h"
using Penjin::Texture;
Texture::Texture() : loaded(false), txID(-1)
{
    //ctor
}

Texture::~Texture()
{
    //dtor
    #if PENJIN_SDL

    #elif PENJIN_GL
    if(loaded)
		glDeleteTextures( 1, &txID);
    #endif
    loaded = false;
}

Penjin::ERRORS Texture::load(Surface* s)
{

}
