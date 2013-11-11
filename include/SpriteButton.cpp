/**
    \section LICENSE
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

Penjin::ERRORS SpriteButton::load(const string& f)
{
    return sprite->load(f);
}

void SpriteButton::render()
{
    //  We need to adjust the button if the sprite is larger
    if(sprite)
         Button::setDimensions(sprite->getDimensions());

    Button::render();
    if(sprite)
    {
        Vector2d<float> a = getScaledDimensions();
        Vector2d<float> b = sprite->getDimensions();
        // The difference of the dimensions of both objects
        a = a - b;
        a = a * 0.5f;
        b = a + getScaledPosition();

        sprite->setPosition(b);
        sprite->render();

    }
}


void SpriteButton::update()
{
    if(sprite)
    {
        sprite->update();
    }
}
