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
#include "DimensionObject.h"
#include "GFX.h"
using Penjin::DimensionObject;

DimensionObject::DimensionObject()
{
    //ctor
    dimensions.x = dimensions.y = 0;
}

DimensionObject::~DimensionObject()
{
    //dtor
}

Vector2d<int> DimensionObject::getDimensions()const
{
    return dimensions;
}

int DimensionObject::getWidth()const
{
    return dimensions.x;
}

int DimensionObject::getHeight()const
{
    return dimensions.y;
}

void DimensionObject::setWidth(const int& w)
{
    dimensions.x = w;
    Renderer* gfx = GFX::getInstance();
    if(gfx->getScaleMode() != smPRESCALE)
        return;

    scaled.x =  (float)(dimensions.x * gfx->getPixelScale().x) + 0.5f;
}

void DimensionObject::setHeight(const int& h)
{
    dimensions.y = h;
    Renderer* gfx = GFX::getInstance();
    if(gfx->getScaleMode() != smPRESCALE)
        return;

    scaled.y = (float)(dimensions.y * gfx->getPixelScale().y) + 0.5f;
}

void DimensionObject::rescale()
{
    Renderer* gfx = GFX::getInstance();
    if(gfx->getScaleMode() != smPRESCALE)
        return;

    scaled = dimensions * gfx->getPixelScale();
}

Vector2d<int> DimensionObject::getScaledDimensions()
{
    return scaled;
}
