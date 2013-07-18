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
#ifndef MENUITEM_H_INCLUDED
#define MENUITEM_H_INCLUDED
#include "SpriteButton.h"
#include "TextObject.h"

namespace Penjin
{
   class MenuItem : public TextObject, public SpriteButton
   {
       public:
           MenuItem()
           {

           }
           virtual ~MenuItem();

           virtual void update();
           virtual void render();

           void setIsSelectable(CRbool isSelectable){this->isSelectable = isSelectable;}
           bool getIsSelectable()const{return isSelectable;}
           void setIsSelected(CRbool isSelected){this->isSelected = isSelected;}
           bool isMouseSelected(CRint x,CRint y);


           //void setHorizontalOffset(CRint offset){horizontalOffset = offset;}
           //int getHorizontalOffset()const{return horizontalOffset;}
           //void setSpacing(CRint spacing){verticalSpacing = spacing;}
           //int getSpacing()const{return verticalSpacing;}
           //MENU_TYPES getType()const{return type;}
           //void setType(const MENU_TYPES& type){this->type = type;}
           virtual void init();
       protected:
           bool isSelected;        //  Is this option currently selected in the menu
           bool isSelectable;      //  Is this option able to be selected in the menu

           //int verticalSpacing;    //  This value is the space to leave above the menu item before renderring
           //int horizontalOffset;   //  This corrects the position from the menu startPos
           //MENU_TYPES type;
   };
}
#endif // MENUITEM_H_INCLUDED
