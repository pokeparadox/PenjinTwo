/*
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
#ifndef RENDERER_H
#define RENDERER_H

//#include "DimensionObject.h"
#include "Singleton.h"
#include "Colour.h"
#include "Surface.h"
#include  <vector>

namespace Penjin
{
    class Timer;
    class RenderObject;

    enum SCALE_MODES
    {
        smNONE=0,           //  No scaling applied
        smSCALE2x,          //  Scale2X filter applied before final blit
        smPRESCALE,         //  Objects resized on load. Positions and dimensions scaled.
        smPOKESCALE,        //  Object prescaled using PokeScale smoothing
    };

    class Renderer
    {
        public:
            /** Default constructor */
            Renderer();
            /** Default destructor */
            virtual ~Renderer();

            void setBitsPerPixel(const int& bpp);
            void setFullscreen(const bool& fs);
            void setClearColour(const Colour& c);
            void setDrawColour(const Colour& c);
            void setDrawWidth(const int& w);
            void setFrameRate(const uint& fps);

            virtual void showCursor(const bool& show)=0;
            /** Sets the currently set width, height and bit-depth to the screen */
            virtual void applyVideoSettings()=0;

            void frameLimiter();
            virtual void clear()=0;
            virtual void blit()=0;

            virtual void queueRenderObject(RenderObject* obj);
            virtual void renderQueue();


            virtual void drawPixel(const Vector2d<float> & v)=0;
            virtual void drawLine(const Vector2d<float> & p1, const Vector2d<float> & p2)=0;
            virtual void drawRectangle(const Vector2d<float> & pos, const Vector2d<int> & dims)=0;
            virtual void drawEllipse(const Vector2d<float> & centre, const float& rx, const float& ry)=0;

            virtual Colour getPixel(Vector2d<int> pos)=0;
            virtual Colour getPixel(Surface* s, Vector2d<int> pos)=0;

            //virtual Surface cropSurface(Surface in, Rectangle cropArea)=0;

            virtual void showVideoInfo()=0;

            void setWidth(const int& w);
            void setHeight(const int& h);
            void setResolution(const Vector2d<int>& r);
            Vector2d<int> getResolution();
            int getWidth();
            int getHeight();
            // Scaling options
            void setScaleMode(const SCALE_MODES& m);            //  Sets the scaling mode
            SCALE_MODES getScaleMode();
            void setBaseResolution(const Vector2d<int>& res);   //  Sets the intended resolution
            void setBaseWidth(const int& w);
            void setBaseHeight(const int& h);
            Vector2d<float> getPixelScale();                    //  Gets the scale Vector of a single pixel.
            virtual Surface* scale(Surface* surface, const float& scale)=0;
            // Smooth scale a Surface based on an integer scale factor
            virtual Surface* pokeScale(Surface* surface, const int& scale)=0;

        protected:
            int bpp;
            uint fps;
            bool fullScreen;
            Colour clearColour;
            Colour drawColour;
            int drawWidth;
            Timer* timer;
            vector <RenderObject*> rendObjs;
            Vector2d<int> resolution;
            // Scaling options
            SCALE_MODES scaleMode;
            Vector2d<int> baseResolution;
            Vector2d<float> pixelScale;
    };
}
#endif // RENDERER_H
