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
#include "StringMenuItem.h"

StringMenuItem::~StringMenuItem()
{
}

void StringMenuItem::init()
{
    setType(MENU_STRING_ITEM);
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif
    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
    verticalSpacing = 0;
    horizontalOffset = 0;
    selectionIndicator = '-';
}

#ifdef PENJIN_SDL
void StringMenuItem::render()
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText + " " + selectionIndicator;
        text->print(out);
        text->setColour(temp);
        return;
    }
    else
        out = "  " + menuItemText + "  ";

    text->print(out);
}
void StringMenuItem::render(SDL_Surface* screen)
{
    text->setPosition(position/*+ Vector2di(horizontalOffset,0)*/);
    string out;
    if(isSelected)
    {
        Colour temp = text->getColour();
        if(temp != selectedColour)
            text->setColour(selectedColour);
        out = selectionIndicator;
        out += " " + menuItemText + " " + selectionIndicator;
        text->print(screen,out);
        text->setColour(temp);
        return;
    }
    else
        out = "  " + menuItemText + "  ";

    text->print(screen,out);
}
#else
void StringMenuItem::render()
{
    #ifndef PENJIN_ASCII
    text->setPosition(position+ Vector3df(horizontalOffset,0.0f,0.0f));
    #endif
    string out;
    #ifndef PENJIN_ASCII
    if(isSelected)
    {
        out = selectionIndicator;
        out += " " + menuItemText + " " + selectionIndicator;
    }
    else
        out = menuItemText;

    text->print(out);
    #else
    cout << menuItemText << endl;
    #endif
}
#endif

#ifndef PENJIN_ASCII
    Vector2di StringMenuItem::getDimensions()
    {
        if(menuItemText.empty())
            return Vector2di(0,0);
        dimensions = text->getDimensions(menuItemText);
        return dimensions;
    }
#endif

