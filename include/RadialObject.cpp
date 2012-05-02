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
*/#include "RadialObject.h"
using Penjin::RadialObject;

RadialObject::RadialObject()
{
    //ctor
}

RadialObject::~RadialObject()
{
    //dtor
}

void RadialObject::setRadius(unsigned int r)
{
    setWidth(r*2);
}

unsigned int RadialObject::getRadius()
{
    return getWidth() * 0.5f;
}

void RadialObject::setRadius2(unsigned int r)
{
    setHeight(r*2);
}

unsigned int RadialObject::getRadius2()
{
    return getHeight() * 0.5f;
}

void RadialObject::setDiameter(unsigned int d)
{
    setWidth(d);
}

unsigned int RadialObject::getDiameter()
{
    return getWidth();
}

void RadialObject::setDiameter2(unsigned int d)
{
    setHeight(d);
}

unsigned int RadialObject::getDiameter2()
{
    return getHeight();
}

