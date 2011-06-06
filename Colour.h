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
#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#include "PenjinTypes.h"
#include "Object.h"
#include <SDL/SDL.h>
#include <algorithm>
using namespace std;
/**
  * \file Colour class allows manipulation of colours
  * \author Kevin Winfield-Pantoja
  */

namespace Penjin
{
    enum COLOURS
    {
        BLACK=0,
        RED,
        LIGHT_RED,
        GREEN,
        LIGHT_GREEN,
        BLUE,
        LIGHT_BLUE,
        YELLOW,
        PURPLE,
        MAGENTA,
        CYAN,
        ORANGE,
        BROWN,
        DARK_GREY,
        GREY,
        LIGHT_GREY,
        WHITE
    };

    class Colour : public Object
    {
        public:
            Colour(){setColour(WHITE);}
            Colour(const SDL_Color& c){setColour(c.r,c.g,c.b);}
            Colour(const uchar& r,const uchar& g,const uchar& b){setColour(r,g,b);}
            Colour(const uchar& r,const uchar& g,const uchar& b,const uchar& a){setColour(r,g,b,a);}
            // the following two are necessary, because gcc does not know whether to convert int to uchar or float
            Colour(CRint r,CRint g,CRint b){setColour(r,g,b);}
            Colour(CRint r,CRint g,CRint b,CRint a){setColour(r,g,b,a);}
            Colour(const COLOURS& colour){setColour(colour);}
            Colour(const Colour& colour)                    // Create a colour using another colour
            {
                r = colour.r;
                g = colour.g;
                b = colour.b;
                a = colour.a;
            }
            Colour (CRint rgb){setColour(rgb);}
            //virtual ~Colour(){;}

            // OpenGL type colour
            Colour(CRfloat r,CRfloat g,CRfloat b,CRfloat a){setOGLColour(r,g,b,a);}
            Colour(CRfloat r,CRfloat g,CRfloat b){setOGLColour(r,g,b,1.0f);}
            void setOGLColour(CRfloat r,CRfloat g,CRfloat b,CRfloat a);
            void setOGLColour(CRfloat r,CRfloat g,CRfloat b){setOGLColour(r,g,b,1.0f);}

            //  Normal colours
            void setColour(const Colour& c){setColour(c.r,c.g,c.b,c.a);}
            void setColour(const uchar& r,const uchar& g,const uchar& b,const uchar& a);	//	Set the colour using RGBA
            void setColour(const uchar& r,const uchar& g,const uchar& b){setColour(r,g,b,255);}            // Set the colour using RGB
            void setColour(const COLOURS& colour);						//	Set the colour using predefines
            void setColour(CRint rgb);                                          // Set the colour using a Delphi int (red + green * 256 + blue * 256 * 256)

            SDL_Color getSDL_Colour();		            //	Converts the stored colour to an SDL_Color object
            Uint32 getSDL_Uint32Colour(const SDL_Surface* dst)const;
            Uint32 getSDL_Uint32Colour(){return getSDL_Uint32Colour(SDL_GetVideoSurface());}
            void convertColour(Uint32 colour,SDL_PixelFormat *format);      //  Converts an SDL Uint32 colour to a Colour object

            Colour getGreyScale();  //  Get this colour as a grayscale colour.
            void toGreyScale(){*this = getGreyScale();}     //  Convert this colour to grayscale


            // Operators
            Colour operator+(const uchar& c)
            {
                return (*this +Colour(c,c,c));
            }
            Colour operator+(const Colour& c)
            {
                Colour b = *this;
                #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                    b.r = min(b.r + c.r,1.0f);
                    b.g = min(b.g + c.g,1.0f);
                    b.b = min(b.b + c.b,1.0f);
                #else
                    b.r = min((uint)b.r + c.r,(uint)255);
                    b.g = min((uint)b.g + c.g,(uint)255);
                    b.b = min((uint)b.b + c.b,(uint)255);
                #endif
                return b;
            }
            Colour operator-(const Colour& c)
            {
                Colour b = *this;
                #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                    b.r = max(b.r - c.r,0.0f);
                    b.g = max(b.g - c.g,0.0f);
                    b.b = max(b.b - c.b,0.0f);
                #else
                    b.r = max(b.r - c.r,0);
                    b.g = max(b.g - c.g,0);
                    b.b = max(b.b - c.b,0);
                #endif
                return b;
            }
            Colour operator-(const uchar& c)
            {
                return (*this -Colour(c,c,c));
            }
            Colour operator*(const Colour& c)
            {
                Colour b = *this;
                #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                    b.r = min(b.r * c.r,1.0f);
                    b.g = min(b.g * c.g,1.0f);
                    b.b = min(b.b * c.b,1.0f);
                #else
                    b.r = min((uint)b.r * c.r,(uint)255);
                    b.g = min((uint)b.g * c.g,(uint)255);
                    b.b = min((uint)b.b * c.b,(uint)255);
                #endif
                return b;
            }
            template <class T>
            Colour operator*(const T& c)
            {
                #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                    r = r*(float)c;
                    g = g*(float)c;
                    b = b*(float)c;
                    return *this;
                #else
                    return (*this * Colour(c,c,c));
                #endif
            }
            Colour operator/(const Colour& c)
            {
                Colour b = *this;
                #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                    b.r = max(b.r / c.r,0.0f);
                    b.g = max(b.g / c.g,0.0f);
                    b.b = max(b.b / c.b,0.0f);
                #else
                    b.r = max(b.r / c.r,0);
                    b.g = max(b.g / c.g,0);
                    b.b = max(b.b / c.b,0);
                #endif
                return b;
            }
            Colour operator/(const uchar& c)
            {
                #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                    float f = 1/(float)c;
                    r = r*f;
                    g = g*f;
                    b = b*f;
                    return *this;
                #else
                    return (*this /Colour(c,c,c));
                #endif
            }
            //Colour operator/(const float& c){return Colour(red/c,green/c,blue/c,alpha);}
            //  Less Than Equal
            bool operator<=(const Colour& c)const{return lessThanEqual(c.r,c.g,c.b,c.a);}
            bool operator<=(const COLOURS& colour)const{return operator<=(Colour(colour));}
            bool lessThanEqual(const uchar& r,const uchar& g,const uchar& b)const{return lessThanEqual(r,g,b,255);}
            bool lessThanEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return (isEqual(r,g,b,a) || lessThan(r,g,b,a));}
            //  Less Than
            bool operator<(const Colour& c)const{return lessThan(c.r,c.g,c.b,c.a);}
            bool operator<(const COLOURS& colour)const{return operator<(Colour(colour));}
            bool lessThan(const uchar& r,const uchar& g,const uchar& b)const{return lessThan(r,g,b,255);}
            bool lessThan(const uchar& r,const uchar& g,const uchar& b,const uchar& a) const;
            //  More Than Equal
            bool operator>=(const Colour& c)const{return moreThanEqual(c.r,c.g,c.b,c.a);}
            bool operator>=(const COLOURS& colour)const{return operator>=(Colour(colour));}
            bool moreThanEqual(const uchar& r,const uchar& g,const uchar& b)const{return moreThanEqual(r,g,b,255);}
            bool moreThanEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return (isEqual(r,g,b,a) || moreThan(r,g,b,a));}
            //  More Than
            bool operator>(const Colour& c)const{return !operator<(c);}
            bool operator>(const COLOURS& colour)const{return !operator<(Colour(colour));}
            bool moreThan(const uchar& r,const uchar& g,const uchar& b)const{return !lessThan(r,g,b,255);}
            bool moreThan(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return !lessThan(r,g,b,a);}

            //  Equivalency
            bool operator==(const Colour& c)const{return isEqual(c.r,c.g,c.b,c.a);}
            bool operator==(const COLOURS& colour)const{return operator==(Colour(colour));}
            bool isEqual(const uchar& r,const uchar& g,const uchar& b)const{return isEqual(r,g,b,255);}
            bool isEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const;

            //  Inequality
            bool operator!=(const Colour& colour)const{return !operator==(colour);}
            bool operator!=(const COLOURS& colour)const{return !operator==(colour);}
            bool notEqual(const uchar& r,const uchar& g,const uchar& b)const{return !isEqual(r,g,b);}
            bool notEqual(const uchar& r,const uchar& g,const uchar& b,const uchar& a)const{return !isEqual(r,g,b,a);}

            //  Negation - Provides the inverse colour
            Colour operator- ()const{return (Colour(WHITE) - *this);}

            //  Channel ops - swap colour channels around
            void swapRG();
            void swapGB();
            void swapRB();

            // Colour data
            #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)
                float r; // Values stores in range 0.0 - 1.0f
                float g;
                float b;
                float a;

                void toGL();
            #else
                uchar r; // 0 - 256 range
                uchar g;
                uchar b;
                uchar a;

                void toNormal();
            #endif
    };
}
#endif // COLOUR_H_INCLUDED
