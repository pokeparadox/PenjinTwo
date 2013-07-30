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
#include "Menu.h"
using Penjin::Menu;
Menu::Menu()
{

}

Menu::~Menu()
{
    clear();
}

void Menu::calcHeight()
{
    int accumHeight = 0;
    Vector2d<float> pixScale = GFX->getPixelScale();
    for(unsigned int i = 0; i < widgets.size(); ++i)
    {
        accumHeight += widgets.at(i)->getHeight() + (pixScale.y * 2);
    }
    setHeight(accumHeight);
}

void Menu::update()
{
    Vector2d<int> dim = getScaledDimensions();
    //Vector2d<int> pos = getScaledPosition();      May use in future to hide Menu to left or right
    Vector2d<int> startPos = startPosition.getScaledPosition();
    Vector2d<float> pixScale = GFX->getPixelScale();
    int yOffset;
    // Now position the widgets
    Vector2d<float> t = Rectangle::getScaledPosition();
    int widestwidth = getWidest()->getWidth();
    setWidth(widestwidth + (pixScale.x * 2));
    calcHeight();
    for(unsigned int i = 0; i < widgets.size(); ++i)
    {
        int wCentre = widgets.at(i)->getScaledDimensions().y*0.5f;
        Vector2d<float> pixScale = GFX->getPixelScale();
        int offset = 1;//(boxCentre -wCentre) + pixScale.x;
        t.x = offset + getScaledPosition().x;
        t.y += offset;

        widgets.at(i)->setPosition(t.x/pixScale.x,t.y/pixScale.y);
        t.y += widgets.at(i)->getScaledDimensions().y;
        widgets.at(i)->setSelected(false);
        widgets.at(i)->setActive(false);
    }

    if(selection > -1 && selection < (int)widgets.size())
        widgets.at(selection)->setSelected(true);
    else
        selection = -1;

    if(padSelection > -1 && padSelection < (int)widgets.size())
        widgets.at(padSelection)->setSelected(true);
    else
        padSelection = -1;
}


/*void Menu::updatePositions()
{
    int s = menuItems.size()-1;
    //  Check for first MenuItem
    menuItems[s]->setPosition(menuStart);
    for(int i = s; i >= 0 ; --i)
    {
        if (s != 0)
        {
            #ifdef PENJIN_3D
                Vector3df pos = menuItems[s-1]->getPosition();
                pos.y += (menuItems[s-1]->getSpacing() - menuItems[s-1]->getDimensions().y);
            #else
                Vector2df pos = menuItems[s-1]->getPosition();
                pos.y += (menuItems[s-1]->getSpacing() + menuItems[s-1]->getDimensions().y);
            #endif
            menuItems[s]->setPosition(pos);
        }
    }
}
*/

