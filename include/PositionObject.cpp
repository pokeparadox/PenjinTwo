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
#include "PositionObject.h"
#include "GFX.h"
using Penjin::PositionObject;

PositionObject::PositionObject()
{
    //ctor
}

PositionObject::~PositionObject()
{
    //dtor
}

Vector2d<float> PositionObject::getPosition()const
{
    return position;
}

void PositionObject::setX(const float& x)
{
    position.x = x;
    Renderer* gfx = GFX::getInstance();
    if(gfx->getScaleMode() != smPRESCALE)
        return;

    scaled.x = position.x * gfx->getPixelScale().x;
}

void PositionObject::setY(const float& y)
{
    position.y = y;
    Renderer* gfx = GFX::getInstance();
    if(gfx->getScaleMode() != smPRESCALE)
        return;
    scaled.y = position.y * gfx->getPixelScale().y;
}

void PositionObject::rescale()
{
    Renderer* gfx = GFX::getInstance();
    if(gfx->getScaleMode() != smPRESCALE)
        return;

    scaled = position * gfx->getPixelScale();
}

Vector2d<float> PositionObject::getScaledPosition()
{
    return scaled;
}
