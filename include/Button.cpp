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

#include "Button.h"
#include "Widget.h"
#include "Rectangle.h"

using Penjin::Button;
using Penjin::Widget;
using Penjin::Rectangle;

Button::Button() : selection(NULL)
{
    //ctor
    setColour(LIGHT_GREY);
    this->setHighLightColour(WHITE);
    this->setLowLightColour(DARK_GREY);
    Vector2d<int> t(24,24);
    setDimensions(t);
    drawWidth = -1;
    selection = new Rectangle();
    selection->setColour(WHITE);
    selection->setDrawWidth(1);
    selection->setDimensions(t.x+2,t.y+2);
    selection->setPosition(position.x-1, position.y-1);
}

Button::~Button()
{
    //dtor
    delete selection;
}

void Button::render()
{
    if(isActive())
        Rectangle::render();
    else if(isSelected())
    {
        if(showWidget)
            Widget::render();
        if(showSelection)
        {
            selection->setDimensions(dimensions.x+2,dimensions.y+2);
            selection->setPosition(position.x-1, position.y-1);
            selection->render();
        }
    }
    else
    {
        if(showWidget)
            Widget::render();
    }

}

void Button::update()
{

}
