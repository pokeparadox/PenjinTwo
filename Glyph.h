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
#ifndef GLYPH_H
#define GLYPH_H

#include "Image.h"
#include <SDL/SDL_ttf.h>
#include "PenjinTypes.h"
#include <ctype.h>

namespace Penjin
{
    namespace GlyphClass
    {
        enum RENDER_MODES
        {
            QUICK,  //  fast with colourkey
            BOXED,  //  antialiased against bg box.
            NICE    //  anitaliased fully with alpha channel SLOW
        };
    }
    using namespace GlyphClass;
    class Glyph : public Image
    {
        public:
            Glyph();
            ~Glyph();

            void refresh(); //  Updates the glyph

            void setFont(TTF_Font* f){font = f;}            //  Set the pointer to the loaded Font object

            void setRenderMode(RENDER_MODES m){renderMode = m;}
            void setCharacter(CRchar c){character = c;}

            void setBgColour(const Colour& c){bgColour = c;}
            void setFontSize(CRuint s){fontSize = s;}

            Colour getBgColour()const{return bgColour;}
            uint getFontSize()const{return fontSize;}
            char getCharacter()const{return character;}

            RENDER_MODES getRenderMode()const{return renderMode;}

        private:
            // Disabled to prevent double freed pointers.
            Glyph(const Glyph& noCopy);
            Glyph& operator=(const Glyph& noCopy);

            //  We can check the below params to see if glyph needs to be recreated.
            char character;
            uint fontSize;

            Colour  bgColour;
            TTF_Font* font;
            GlyphClass::RENDER_MODES renderMode;
    };

}


#endif // GLYPH_H
