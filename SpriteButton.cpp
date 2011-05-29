/**
    \section LICENSE
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
**********************************************************************************************/
/**
  * \file SpriteButton is a class to create a button with an image centred on button face.
  * \author Kevin Winfield-Pantoja
*/
#include "SpriteButton.h"
#include "Sprite.h"
using Penjin::SpriteButton;
using Penjin::Sprite;

SpriteButton::SpriteButton() : sprite(NULL)
{
    //ctor
    sprite = new Sprite;
}

SpriteButton::~SpriteButton()
{
    //dtor
    delete sprite;
}

Penjin::ERRORS SpriteButton::loadImage(const string& f)
{
    Penjin::ERRORS e;
    e = sprite->load(f);
    if(e == PENJIN_OK)
    {
        sprite->setTransparentColour(Vector2d<int>(0,0));
        Vector2d<int> a = getDimensions();
        Vector2d<int> b = sprite->getDimensions();
        if(a < b)
        {
            setDimensions(b);
        }
        a = a - b;
        a = a * 0.5f;
        b = sprite->getPosition() + Vector2d<float>(a.x,a.y);
        sprite->setPosition(b);
    }
    return e;
}

void SpriteButton::render()
{
    Button::render();
    Vector2d<int> a = getDimensions();
    Vector2d<int> b = sprite->getDimensions();
    a = a - b;
    b.x = position.x + a.x;
    b.y = position.y + a.y;
    a = sprite->getDimensions() *0.5f;
    b = b - a;
    sprite->setPosition(b);
    sprite->render();
}


void SpriteButton::update()
{

}
