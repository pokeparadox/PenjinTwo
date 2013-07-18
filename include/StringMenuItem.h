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
#ifndef STRINGMENUITEM_H_INCLUDED
#define STRINGMENUITEM_H_INCLUDED

#ifndef PENJIN_ASCII
    #include "Text.h"
#else
    #include <iostream>
    using std::cout;
    using std::endl;
#endif
#include "MenuItem.h"

class StringMenuItem : public MenuItem
{
    public:
        StringMenuItem(){init();}
        StringMenuItem(CRstring menuItemText){init(); this->menuItemText = menuItemText;}
        #ifndef PENJIN_ASCII
            StringMenuItem(Text* pointer){init(); setTextHandler(pointer);}
        virtual Vector2di getDimensions();                   // renderstoa null surfaxe in order to get the dims
        #endif
        virtual ~StringMenuItem();

        virtual void update(){;}                          //  We just return since there is nothing to update for this type


        virtual void render();
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #endif

        /// Set text properties - inherited from the text handler passed in
        #ifndef PENJIN_ASCII
            void setTextHandler(Text* pointer){text = pointer;}
            void setTextSelectionColour(const Colour& c){selectedColour = c;}
        #endif
        void setMenuItemText(CRstring text){menuItemText = text;}
        void setSelectionIndicator(CRchar c){selectionIndicator = c;}

    protected:
        virtual void init();

    private:
        string menuItemText;
        #ifndef PENJIN_ASCII
            Text* text;             //   Pointer to a Text the actual Text is shared through the menu items
            Colour selectedColour;
        #endif
        char selectionIndicator;
};

#endif // STRINGMENUITEM_H_INCLUDED
