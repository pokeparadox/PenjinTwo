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
#include "DirMenuItem.h"
using Penjin::DirMenuItem;

DirMenuItem::DirMenuItem()
{
    init();
}

DirMenuItem::~DirMenuItem()
{
}

void DirMenuItem::init()
{
    //setType(MENU_DIR_ITEM);
    position.x = 0;
    position.y = 0;

    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
//    verticalSpacing = 0;
//    horizontalOffset = 0;
    selectionIndicator = '>';
    dirType = -1; // UNKNOWN
}

void DirMenuItem::render()
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText;
        text->print(out);
        text->setColour(temp);
        return;
    }
    else
        out = menuItemText;

    text->print(out);
}

#ifndef PENJIN_ASCII
    Vector2di DirMenuItem::getDimensions()
    {
        if(menuItemText.empty())
            return Vector2di(0,0);
        dimensions = text->getDimensions(menuItemText);
        return dimensions;
    }
#endif
