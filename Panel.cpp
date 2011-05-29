/*-
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
#include "GFX.h"
#include "SimpleJoy.h"

#include "Panel.h"
#include "Vector2d.h"
#include "Widget.h"
#include "Line.h"
using Penjin::Panel;
using Penjin::Vector2d;
using Penjin::Widget;
using Penjin::Line;
Panel::Panel() : shouldHide(false), hidden(false), selection(-1)//, hideOffset(0)
{
    //ctor
    //setColour(DARK_GREY);
    Vector2d<int> t = Penjin::GFX::getInstance()->getDimensions();
    t.y = t.y * 0.18f;
    t.x = t.x -1;
    setDimensions(t);
    lowLight->setColour(BLACK);
    highLight->setColour(LIGHT_GREY);
    setColour(DARK_GREY);
    drawWidth = -1;
}

Panel::~Panel()
{
    //dtor
    for(int i = widgets.size()-1; i>=0; --i)
    {
        delete widgets.at(i);
    }
    widgets.clear();
}

void Panel::addWidget(Widget* w)
{
    if(w != NULL)
        widgets.push_back(w);
}

void Panel::render()
{
    Widget::render();
    // Render the widgets on the bar
    for(unsigned int i = 0; i < widgets.size(); ++i)
    {
        widgets.at(i)->render();
    }
}

void Panel::update()
{
    // first we find out if the panel is near top or bottom of screen
    int centre = Penjin::GFX::getInstance()->getDimensions().y * 0.5f;
    int boxCentre = ( startPosition.y + dimensions.y) * 0.5f;

    // nearer top of screen
    if(boxCentre<centre)
    {
        if(shouldHide)
        {
            if(Rectangle::position.y >= startPosition.y - dimensions.y)
                --Rectangle::position.y;
            else
                hidden = true;
        }
        else
        {
            if(Rectangle::position.y  < startPosition.y)
                ++Rectangle::position.y;
            else
                hidden = false;
        }
    }
    else    // near bottom
    {
        // TODO
    }


    // Now position the widgets
    Vector2d<float> t = Rectangle::position;
    for(unsigned int i = 0; i < widgets.size(); ++i)
    {
        // resize panel if a wdiget is too big
        if(widgets.at(i)->getDimensions() > getDimensions())
            setDimensions(widgets.at(i)->getDimensions());

        int wCentre = widgets.at(i)->getDimensions().y*0.5f;
        int offset = (boxCentre -wCentre) +1;
        t.x += offset;
        t.y = offset + position.y;
        widgets.at(i)->setPosition(t.x,t.y);
        t.x += widgets.at(i)->getDimensions().x;
        widgets.at(i)->setSelected(false);
        widgets.at(i)->setActive(false);
    }

    if(selection > -1 && selection < (int)widgets.size())
        widgets.at(selection)->setSelected(true);
    else
        selection = -1;
}

void Panel::selectionConfirm()
{
    if(selection > -1 && selection < (int)widgets.size())
        widgets.at(selection)->setActive(true);
    else
        selection = -1;
}

int Panel::whichWidget()
{
    // first check if the panel is even selected
    if(isMouseSelected())
    {
        // Then check if panel is active
        for(int i = widgets.size()-1; i>=0; --i)
        {
            if(widgets.at(i)->isMouseSelected())
                selection = i;
            if(widgets.at(i)->isActive())
            {
                return i;
            }
        }
    }
    else if(Joy::getInstance()->isLeftClick())
    {
        // if we click outside the panel we hide the panel
        setShouldHide(true);
    }
    return -1;
}

bool Panel::isHidden()
{
    return hidden;
}

void Panel::toggleHidden()
{
    shouldHide = !shouldHide;
}

void Panel::setShouldHide(const bool& hide)
{
    shouldHide = hide;
}

void Panel::selectionNext()
{
    ++selection;
}

void Panel::selectionPrevious()
{
    --selection;
}
