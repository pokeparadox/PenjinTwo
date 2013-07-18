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
#ifndef DIRMENUITEM_H
#define DIRMENUITEM_H

#include "MenuItem.h"
#include "Text.h"
#ifdef _WIN32
    //#include <direct.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <stdlib.h>
    #define DT_DIR _S_IFDIR
    #define DT_REG _S_IFREG
#else
    #include <dirent.h>
    #include <unistd.h>
    //#include <sys/stat.h>
    #include <limits.h>
    #define _MAX_PATH PATH_MAX
    #ifdef PLATFORM_WII
        #define DT_DIR 4
        #define DT_REG 8
    #endif
#endif

namespace Penjin
{
    class DirMenuItem : public MenuItem
    {
        public:
            DirMenuItem();
            #ifndef PENJIN_ASCII
                DirMenuItem(Text* pointer){init(); setTextHandler(pointer);}
                virtual Vector2di getDimensions();                   // renderstoa null surfaxe in order to get the dims
            #endif
            virtual ~DirMenuItem();


            virtual void update(){;}


            virtual void render();

            /// Set text properties - inherited from the text handler passed in
            #ifndef PENJIN_ASCII
                void setTextHandler(Text* pointer){text = pointer;}
                void setTextSelectionColour(const Colour& c){selectedColour = c;}
            #endif
            void setMenuItemText(CRstring text){menuItemText = text;}
            void setSelectionIndicator(CRchar c){selectionIndicator = c;}
            void setDirType(CRint t){dirType = t;}
            int getDirType()const{return dirType;}

        protected:
            virtual void init();

        private:
            string menuItemText;
            int dirType;
            #ifndef PENJIN_ASCII
                Text* text;             //   Pointer to a Text the actual Text is shared through the menu items
                Colour selectedColour;
            #endif
            char selectionIndicator;
    };
}

#endif // DIRMENUITEM_H
