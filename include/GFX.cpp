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
#include "ErrorHandler.h"
using Penjin::Renderer;
using Penjin::GPU;
using Penjin::ERRORS;

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
        #if PENJIN_CONSOLE
            if (engine == "Console")
            {
                renderer = GFX_CONSOLE_2D::getInstance();
                #ifdef _DEBUG
                ErrorMan::getInstance()->print(PENJIN_OK,"GPU::setMode(Console,2)");
                #endif
            }
        #else
            if(engine == "SDL")
            {
                renderer = GFX_SDL_2D::getInstance();
                #ifdef _DEBUG
                ErrorMan::getInstance()->print(PENJIN_OK,"GPU::setMode(SDL,2)");
                #endif
            }
            #ifdef PENJIN_GL
            else if (engine == "GL")
            {
                renderer = GFX_GL_2D::getInstance();
                #ifdef _DEBUG
                ErrorMan::getInstance()->print(PENJIN_OK,"GPU::setMode(GL,2)");
                #endif
            }
            #endif
            else
            {
                renderer = GFX_SDL_2D::getInstance();
                string out = "GPU::setMode(" + engine + ",2) - Invalid GFX Engine: " + engine;
                ErrorMan::getInstance()->print(PENJIN_ERROR,out);
                out = "GPU::setMode(" + engine + ",2) - Defaulting to SDL 2D.";
                ErrorMan::getInstance()->print(PENJIN_ERROR,out);
            }
        #endif // PENJIN_CONSOLE
    }
#ifdef PENJIN_3D
    else if(dims == 3)
    {
        if(engine == "SDL")
        {
            renderer = GFX_SDL_3D::getInstance();
            #ifdef _DEBUG
                ErrorMan::getInstance()->print(PENJIN_OK,"GPU::setMode(SDL,3)");
            #endif
        }
        #ifdef PENJIN_GL
        else if (engine == "GL")
        {
            renderer = GFX_GL_3D::getInstance();
            #ifdef _DEBUG
                ErrorMan::getInstance()->print(PENJIN_OK,"GPU::setMode(GL,3)");
                #endif
        }
        #endif
        else
        {
            renderer = GFX_SDL_3D::getInstance();
            string out = "GPU::setMode(" + engine + ",3) - Invalid GFX Engine: " + engine;
            ErrorMan::getInstance()->print(PENJIN_ERROR,out);
            out = "GPU::setMode(" + engine + ",3) - Defaulting to SDL 3D.";
            ErrorMan::getInstance()->print(PENJIN_ERROR,out);
        }
    }
#endif
}
