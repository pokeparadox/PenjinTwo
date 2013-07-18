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
*   \file RendererSDL_2d is a 2d renderer using SDL.
*   \author Kevin Winfield-Pantoja
*/

#ifndef RENDERERSDL_2D_H
#define RENDERERSDL_2D_H

#include "Renderer.h"

namespace Penjin
{
    class Surface;
    class Rectangle;

    class RendererSDL_2d : public Renderer
    {
        public:
            //static RendererSDL_2d* getInstance();
            /** Default constructor */
            RendererSDL_2d();
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
            /**< lock the screen */
            virtual void lock();
            /**< unlock the screen */
            virtual void unlock();

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

            /** \brief Draws an Circle on the screen, depending on the renderer's Colour and line width.
             * \param centre : The 2d vector of the centre position of the Circle in pixels.
             * \param r : The float of the radius in pixels.
             */
            virtual void drawCircle(const Vector2d<float> & centre, const float& r);

            /** \brief Draws an Ellipse on the screen, depending on the renderer's Colour and line width.
             * \param centre : The 2d vector of the centre position of the Ellipse in pixels.
             * \param rx : The float of the horizontal radius in pixels.
             * \param ry : The float of the vertical radius in pixels.
             */
            virtual void drawEllipse(const Vector2d<float> & centre, const float& rx, const float& ry);


            virtual Colour getPixel(Vector2d<int> pos);
            virtual Colour getPixel(Surface* s, Vector2d<int> pos);

            virtual Surface* scale(Surface* surface,const float& scale);

            /** \brief SmoothScales a Surface based on an integer scale factor (Not intended for realtime...)
             * \param surface : The Surface image source to scale.
             * \param scale : The integer scale factor.
             * \return The scale Surface.
             */
            virtual Surface* pokeScale(Surface* surface, const int& scale);

            virtual void showVideoInfo();

            //  Deprecated
            Colour getPixel(SDL_Surface* s, Vector2d<int> pos);
            SDL_Surface* getSDLVideoSurface();
            SDL_Surface* cropSurface(SDL_Surface* in, SDL_Rect* cropArea);

            void lockSurface(SDL_Surface* s);
            void unlockSurface(SDL_Surface* s);

        protected:

            /** Default destructor */
            virtual ~RendererSDL_2d();
            SDL_Surface* screen;
        private:
            // Used in PokeScale
            Rectangle findLeftSlope(const Vector2d<int>& px, Surface* in);
            Rectangle findRightSlope(const Vector2d<int>& px, Surface* in);
            void drawSlopes(const Rectangle& L, const Rectangle& R, const int& scale, Surface* out);



            //static RendererSDL_2d* instance;
    };

    //typedef Singleton<RendererSDL_2d> GFX;
}
#endif // RENDERERSDL_2D_H
