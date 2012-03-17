/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

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
    Renderer* gfx = GFX;
    // If we are not scaling, then the scaled size is the same
    if(gfx->getScaleMode() == smNONE)
        scaled.x = x;
    else
        scaled.x =  (float)(position.x * gfx->getPixelScale().x) + 0.5f;
}

void PositionObject::setY(const float& y)
{
    position.y = y;
    Renderer* gfx = GFX;
     // If we are not scaling, then the scaled size is the same
    if(gfx->getScaleMode() == smNONE)
        scaled.y = y;
    else
        scaled.y =  (float)(position.y * gfx->getPixelScale().y) + 0.5f;
}

float PositionObject::getX()
{
    return position.x;
}

float PositionObject::getY()
{
    return position.y;
}

void PositionObject::rescale()
{
    Renderer* gfx = GFX;
    if(gfx->getScaleMode() == smNONE)
        scaled = position;
    else
        scaled = position * gfx->getPixelScale();
}

Vector2d<float> PositionObject::getScaledPosition()
{
    return scaled;
}
