/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

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
#ifndef TEXT_H
#define TEXT_H
//#if defined(PENJIN_SDL) || defined(PENJIN_GL) || defined(PENJIN_SOFT) || defined(PENJIN_ES) || defined(PENJIN_ES2)
    #include "Glyph.h"
//#endif
#include <string>
#include "DoubleVector.h"
#include <ctype.h>
#ifdef PLATFORM_WII
    #include "Penjin.h"
#endif
using namespace std;
#include "PenjinTypes.h"
//#include "Colour.h"
#include "Errors.h"
#include "Singleton.h"
///Text will wrap after 58 characters, inc spaces and punctuation. (at size 12 pt) (on a GP2X screen, 320x240)
///The text below shows how many characters can be used before the text will wrap.
////////////////////////////////////////////////////////////////////////////////////
///text.print(screen, "To be or not to be, that is the question Whether tis noble");


namespace Penjin
{
    namespace TextClass
    {
        enum ALIGNMENT
        {
            LEFT_JUSTIFIED,
            CENTRED,
            RIGHT_JUSTIFIED
        };

            Penjin::ERRORS init();                          //  Must be called once before any Text objects are used.
            void deInit();                        //  Must be called once before program termination.
            bool isInitialised();
    }

    using namespace TextClass;
    class Colour;

    class Text : public Rectangle, public FileObject
    {
        public:
            Text();		//	Initialise font handling
            virtual ~Text();	//	Shutdown font handling
            //static Text* getInstance();

            Penjin::ERRORS load(CRstring fontName,CRuint fontSize);		//	Loads a TTF
            Penjin::ERRORS load(CRstring fontName);  // Load a TTF without changing size

            virtual Penjin::ERRORS save(CRstring fontName);

            void unload();      // Unload the font

            Penjin::ERRORS setFontSize(CRuint s);
            uint getFontSize()const{return fontSize;}
            //  Sets the starting position of the text


            void setBgColour(const Colour& col){*bgColour = col;setRenderMode(GlyphClass::BOXED);}
            Colour getBgColour()const{return *bgColour;}

            void setWrapping(CRbool shouldWrap){wrapText = shouldWrap;}
            bool getWrapping()const{return wrapText;}
            void setAlignment(const ALIGNMENT& align){alignment = align;}
            ALIGNMENT getAlignment()const{return alignment;}
            void setStyle(CRint style){TTF_SetFontStyle(font, style);}
            int getStyle()const{return TTF_GetFontStyle(font);}
            bool isMonoSpaced()const{return TTF_FontFaceIsFixedWidth(font);}
            void setRenderMode(const GlyphClass::RENDER_MODES& m);
            GlyphClass::RENDER_MODES getRenderMode()const;

            /** \brief Get the dimensions of the str*/
            Vector2d<int> getDimensions(CRstring str);

            Vector2d<int> getCursorPosition()const{return cursorPos.getPosition();}
            void setCursorPosition(const Vector2d<int> p){cursorPos.setPosition(p);}



            void setRelativity(CRbool rel){relativePos = rel;}
            //void setCentreText(CRbool centre){centreText = centre;} /// WARNING needs some work!

            ///	You must have used the above functions in order to use the following print functions
            void print(char* text);		//	write a char* string to the screen
            void print(const char* text);
            void print(CRstring text);       //	write a string to the screen
            //	write an integer to the screen
            void print(CRint number);
            //	write a float number to the screen
            void print(CRfloat number);

            // Clear out the Glyphs
            void clear();
        private:
            void print(SDL_Surface* screen, CRstring text);
            void align(const Vector2d<int>& dims);
            void calcDimensions();
            void newLine();
            TTF_Font* font;
            string fontName;
            uint fontSize;
            PositionObject cursorPos;
            // Printable area for text.
            DimensionObject textBox;


            #ifdef PENJIN_SDL
                SDL_Surface* screen;
            #endif
            DoubleVector<Glyph*> glyphs;  //  stores each individual charactor for printing. [FONT_SIZE][CHARACTER]

            bool relativePos;
            bool wrapText;
            ALIGNMENT alignment;

            Colour* bgColour;

            //static Text* instance;
    };

    typedef Singleton<Text> TextMan;
    //typedef Text TextMan;
}

#endif	//	TEXT_H

