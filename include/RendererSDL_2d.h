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
*   \file RendererSDL_2d is a 2d renderer using SDL.
*   \author Kevin Winfield-Pantoja
*/

#ifndef RENDERERSDL_2D_H
#define RENDERERSDL_2D_H

#include "Renderer.h"

namespace Penjin
{
    class RendererSDL_2d : public Renderer
    {
        public:
            /** Default constructor */
            RendererSDL_2d();
            /** Default destructor */
            virtual ~RendererSDL_2d();

            /** \brief Choose whether to show the cursor or not.
             * \param show : whill show the cursor if set to true, false will hide the cursor.
             */
            virtual void showCursor(const bool& show);
            /** Sets the currently set width, height and bit-depth to the screen */
            virtual void applyVideoSettings();

            /**< clears the screen */
            virtual void clear();
            /**< renders the graphics to screen */
            virtual void blit();

            /** \brief Draws a pixel to the screen, depending on the renderer's Colour and line width.
             * \param v : The 2d vector of the position to render on screen in pixels
             */
            virtual void drawPixel(const Vector2d<float> & v);

            // deprecated
            void drawPixel(SDL_Surface* s, const Vector2d<float> & v);

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
            virtual Colour getPixel(Surface s, Vector2d<int> pos);



            virtual void showVideoInfo();

            //  Deprecated
            Colour getPixel(SDL_Surface* s, Vector2d<int> pos);
            SDL_Surface* getSDLVideoSurface();
            SDL_Surface* cropSurface(SDL_Surface* in, SDL_Rect* cropArea);
            void lockSurface(SDL_Surface* s);
            void unlockSurface(SDL_Surface* s);

        private:
            SDL_Surface* screen;
    };

typedef Singleton <RendererSDL_2d> GFX;
}
#endif // RENDERERSDL_2D_H
