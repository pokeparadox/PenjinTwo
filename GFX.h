#ifndef GFX_H_INCLUDED
#define GFX_H_INCLUDED

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
*   \file GFX.h is a wrapper that ensures the correct renderer Singleton is included based on defines.
*   \author Kevin Winfield-Pantoja
*/

#if defined(PENJIN_SDL_VIDEO) || defined(PENJIN_SDL) && !defined(PENJIN_GL_VIDEO)
    #include "RendererSDL_2d.h"
#elif defined(PENJIN_SDL_GL_VIDEO) || defined(PENJIN_GL)
    // #include "RendererSDL_GL_2d.h"
#endif

#endif // GFX_H_INCLUDED
