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
  * \file BRad (Binary Radian) class
  * \author Kevin Winfield-Pantoja
*/
#include "Brad.h"
#include "NumberUtility.h"
#include <cmath>

#ifndef PI
    #define PI 3.141592654f
#endif
using Penjin::Brad;
Brad::Brad() : brad(0)
{
    //ctor
}

/*Brad::Brad(const Brad& b)
{
    brad = b.getAngle();
}*/

Brad::Brad(const float& deg)
{
    setAngleDegrees(deg);
}

Brad::Brad(const unsigned char& bradRAW)
{
    brad = bradRAW;
}

Brad::~Brad()
{
    //dtor
}

void Brad::setAngleDegrees(float degrees)
{
    degrees = NumberUtility::wrapValue(degrees,359.0f);
    brad = degrees * 32 * 0.02222222f;
}

void Brad::setAngleRadians(const float& rad)
{
    setAngleDegrees(rad * PI * 0.005555556f);
}

void Brad::setAngle(Brad b)
{
    brad = b.getAngle();
}

void Brad::setAngle(const unsigned char& bradRAW)
{
    brad = bradRAW;
}

float Brad::getAngleDegrees()
{
    return brad * 45 * 0.03125f;
}

float Brad::getAngleRadians()
{
    return getAngleDegrees() * 180 * (1/PI);
}

unsigned char Brad::getAngle()
{
    return brad;
}
