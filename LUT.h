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
#ifndef LUT_H_INCLUDED
#define LUT_H_INCLUDED

/*
Pirate Games
Lookup tables for Trig functions intended for use on limited systems.
Uses 256 devisions per circle rather than 360
Written by Kevin Winfield-Pantoja
*/
#include "PenjinTypes.h"
#include "NumberUtility.h"
#include <cmath>

#ifndef PI
    #define PI 3.141592654f
#endif

namespace LUT
{
    /// Setup - MUST be init before use!
    void init();
    void deInit();
    /// Trig functions
    float Lsin(uchar angle);
    float Lcos(CRuchar angle);
    float Ltan(uchar angle);
    // Trig functions with interpolation between values
    // Caution, will not be accurate.
    float LIsin(float angle);
    float LIcos(float angle);
    float LItan(float angle);

    /// Conversion
    uchar degreeToBrad(float angle);
    uchar radianToBrad(CRfloat angle);
    float bradToDegree(CRuchar angle);
    float bradToRadian(CRuchar angle);

    //  These are all to avoid divisions.
    const float POINT_ZERO_ZERO_FIVE_FIVE = 0.005555556f;
    const float POINT_ZERO_TWO_TWO = 0.02222222f;
    const float POINT_ZERO_THREE_ONE = 0.03125f;
    const float ONE_OVER_TWOFIVESIX = 0.00390625f;
    const float ONE_OVER_PI = 0.318309886f;
}
#endif // LUT_H_INCLUDED
