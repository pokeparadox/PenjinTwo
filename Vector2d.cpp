/*
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
#include "Vector2d.h"
using Penjin::Vector2d;

Vector2d::Vector2d() : y(0)
{
    //ctor
}

Vector2d::Vector2d(CRint xVal, CRint yVal) : x(xVal), y(yVal)
{

}

Vector2d::Vector2d(const Vector1d& v) : x(v.x), y(0)
{

}

Vector2d::Vector2d(const Vector2d& v) : x(v.x), y(v.y)
{

}

Vector2d::~Vector2d()
{
    //dtor
}

int Vector2d::getY()const
{
    return y;
}

float Vector2d::lengthSquared()const
{
    return (float)(x*x + y*y);
}

float Vector2d::length()const
{
    return sqrt(lengthSquared());
}

Vector2d Vector2d::unit()
{
    float len = length();
    if(len == 0)
        return Vector2d(0,1);

    float temp = 1/len
    return Vector2d(x*temp,y*temp);
}

void Vector2d::normalise()
{
    this = unit();
}

bool Vector2d::equals(const Vector1d& v)
{
    if(y != 0)
        return false;

    return (x == v.x);
}
