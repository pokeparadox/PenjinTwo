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
*   \file RendererGL_2d is 2d Renderer using OpenGL/ES.
*   \author Kevin Winfield-Pantoja
*/

#ifndef RENDERERGL_2D_H
#define RENDERERGL_2D_H

#if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
#define PENJIN_SDL_VIDEO
#include "RendererSDL_2d.h"

namespace Penjin
{
    class RendererGL_2d : public RendererSDL_2d
    {
        public:
            /** Default constructor */
            RendererGL_2d();
            /**Get a static instance of the renderer*/
            //static RendererGL_2d* getInstance();

            /** Sets the currently set width, height and bit-depth to the screen */
            virtual void applyVideoSettings();

            /** inits the GL window for 2D rendering*/
            void initRendering2d();

            /** clears the screen */
            virtual void clear();
            /** renders graphics to the screen. */
            virtual void blit();

            /** \brief Draws a pixel to the screen, depending on the renderer's Colour and line width.
            * \param v : The 2d vector of the position to render on screen in pixels
            */
            virtual void drawPixel(const Vector2d<float> & v);


            /** \brief Draws a Line on the screen, depending on the renderer's Colour and line width.
             * \param p1 : The 2d vector of the starting position of the line in pixels.
             * \param p2 : The 2d vector of the ending position of the line in pixels.
             */
            virtual void drawLine(const Vector2d<float> & p1, const Vector2d<float> & p2);

            /** \brief Draws a Rectangle on the screen, depending on the renderer's Colour and line width.
             * \param pos : The 2d vector of the top-left position of the Rectangle in pixels.
             * \param dims : The 2d vector of the densions of the Rectangle in pixels.
             */
            virtual void drawRectangle(const Vector2d<float> & pos, const Vector2d<int> & dims);

            /** \brief Draws an Ellipse on the screen, depending on the renderer's Colour and line width.
             * \param centre : The 2d vector of the centre position of the Ellipse in pixels.
             * \param rx : The 2d vector of the horizontal radius in pixels.
             * \param ry : The 2d vector of the vertical radius in pixels.
             */
            virtual void drawEllipse(const Vector2d<float> & centre, const float& rx, const float& ry);

            virtual Colour getPixel(Vector2d<int> pos);
        protected:
            /** Default destructor */
            virtual ~RendererGL_2d();

            #if defined(PENJIN_ES) || defined(PENJIN_ES2)
                // X11 variables
                Window				x11Window	= 0;
                Display*			x11Display	= 0;
                long				x11Screen	= 0;
                XVisualInfo*		x11Visual	= 0;
                Colormap			x11Colormap	= 0;

                // EGL variables
                EGLDisplay			eglDisplay	= 0;
                EGLConfig			eglConfig	= 0;
                EGLSurface			eglSurface	= 0;
                EGLContext			eglContext	= 0;
                enum
                {
                _NET_WM_STATE_REMOVE =0,
                _NET_WM_STATE_ADD = 1,
                _NET_WM_STATE_TOGGLE =2
                };

            #endif
        private:
            //static RendererGL_2d* instance;
    };
    //typedef RendererGL_2d GFX;
}
#endif  // GL or ES or ES2 only
#endif  // RENDERERGL_2D_H
