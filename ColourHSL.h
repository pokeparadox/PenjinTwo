/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

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
#ifndef COLOURHSL_H
#define COLOURHSL_H
#include "Colour.h"

class ColourHSL
{
    public:
        ColourHSL();
        ColourHSL(const Colour& c){setColour(c);}
        ColourHSL(const ColourHSL& c){setColour(c);}
        ColourHSL(CRuchar h,CRuchar s, CRuchar l){setColour(h,s,l);}
        ColourHSL(CRuchar h,CRuchar s, CRuchar l, CRuchar a){setColour(h,s,l,a);}

        ///  set the Colour
        // OpenGL type HSL colour
        void setColour(CRfloat h,CRfloat s,CRfloat l,CRfloat a);
        void setColour(CRfloat h,CRfloat s,CRfloat l){setColour(h,s,l,1.0f);}

        //  Normal HSL colours
        void setColour(const Colour& c); // Convert from RGB colour
        void setColour(const ColourHSL& c);
        void setColour(const uchar& h,const uchar& s,const uchar& l,const uchar& a);
        void setColour(const uchar& h,const uchar& s,const uchar& l){setColour(h,s,l,255);}
        void setColour(const PENJIN_COLOURS& c){setColour(Colour(c));}//	Set the colour using predefines

        // Convert to RGBA Colour object
        Colour getColourRGBA();

        //  ColourHSV data
        uchar hue;
        uchar saturation;
        uchar lightness;
        uchar alpha;
};

#endif // COLOURHSL_H
