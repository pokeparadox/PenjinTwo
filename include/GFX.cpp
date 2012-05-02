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
*   \file CLASS_NAME is INSERT DESCRIPTION
*   \author Kevin Winfield-Pantoja
*/
#include "GFX.h"
using Penjin::Renderer;
using Penjin::GPU;

GPU::GPU()
{

}

GPU::~GPU()
{

}

void GPU::setMode(const string& engine, const unsigned int& dims)
{
    if(dims == 2)
    {
        if(engine == "SDL")
            renderer = GFX_SDL_2D::getInstance();
        #ifdef PENJIN_GL
        else if (engine == "GL")
            renderer = GFX_GL_2D::getInstance();
        #endif
    }
    #ifdef PENJIN_3D
    else if(dims == 3)
    {
        if(engine == "SDL")
            renderer = GFX_SDL_3D::getInstance();
        #ifdef PENJIN_GL
        else if (engine == "GL")
            renderer = GFX_GL_3D::getInstance();
        #endif
    }
    #endif
}
