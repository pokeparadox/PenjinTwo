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
  * \file SpritePanel is a Panel object which can use a Sprite as a background
  * \author Kevin Winfield-Pantoja
*/
#include "SpritePanel.h"
#include "Sprite.h"
using Penjin::SpritePanel;
using Penjin::Sprite;

SpritePanel::SpritePanel() : sprite(NULL)
{
    //ctor
    sprite = new Sprite;
}

SpritePanel::~SpritePanel()
{
    //dtor
    delete sprite;
}


void SpritePanel::render()
{
    Panel::render();
    sprite->render();
}

Penjin::ERRORS SpritePanel::loadImage(const string& file)
{
    ERRORS e = sprite->load(file);

    return e;
}
