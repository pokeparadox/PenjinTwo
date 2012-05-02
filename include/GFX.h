#ifndef GFX_H_INCLUDED
#define GFX_H_INCLUDED

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
*   \file GFX.h is a wrapper that ensures the correct renderer Singleton is included based on defines.
*   \author Kevin Winfield-Pantoja
*/
#include <string>
using std::string;
#include "Singleton.h"

#include "Renderer.h"
 #include "RendererSDL_2d.h"
#if PENJIN_GL
    #include "RendererGL_2d.h"
#endif

#ifdef PENJIN_3D
    #include "RendererSDL_3d.h"
    #if PENJIN_GL
        #include "RendererGL_3d.h"
    #endif
#endif

namespace Penjin
{
    typedef Singleton<RendererSDL_2d> GFX_SDL_2D;
    #ifdef PENJIN_GL
        typedef Singleton<RendererGL_2d> GFX_GL_2D;
    #endif
    #ifdef PENJIN_3D
        typedef Singleton<RendererSDL_3d> GFX_SDL_3D;
        #ifdef PENJIN_GL
            typedef Singleton<RendererGL_3d> GFX_GL_3D;
        #endif
    #endif
    class GPU
    {
        public:
            GPU();
            virtual ~GPU();
            void setMode(const string & engine, const unsigned int& dims);
            Renderer* renderer;
    };
    typedef Singleton<GPU> GPU_SINGLETON;
    #define GFX  GPU_SINGLETON::getInstance()->renderer
}

#endif // GFX_H_INCLUDED
