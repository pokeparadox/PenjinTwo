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
#include "LUT.h"
#include <cmath>

#ifndef PI
    #define PI 3.141592654f
#endif
namespace LUT
{
    /// Variables
    const float FIXED_PI = PI;  //Should work for PENJIN_FIXED
    float* sinCos;
    float* tanTable;
}

void LUT::init()
{
    sinCos = tanTable = NULL;
    sinCos = new float[128];    //  floats will be swapped to fixed types with the #define PENJIN_FIXED
    tanTable = new float[128];
    for(uint i = 0; i < 128; ++i)
    {
        //  1/256 = 0.00390625f
        #ifdef PENJIN_FIXED
            sinCos[i] = sin(fixedpoint::fix2float(i * (2*PI)*ONE_OVER_TWOFIVESIX));
            tanTable[i] = tan(fixedpoint::fix2float(i * (2*PI)*ONE_OVER_TWOFIVESIX));
        #else
            sinCos[i] = sin(i * (2*PI)*ONE_OVER_TWOFIVESIX);
            tanTable[i] = tan(i * (2*PI)*ONE_OVER_TWOFIVESIX);
        #endif
    }

}

void LUT::deInit()
{
    if(sinCos)
    {
        delete [] sinCos;
        sinCos = NULL;
    }
    if(tanTable)
    {
        delete [] tanTable;
        tanTable = NULL;
    }
}

float LUT::Lsin(Brad angle)
{
    //  Wrapping should be done automatically for us due to storage limits of uchar
    unsigned char t = angle.getAngle();
    if(t > 128)
    {
        t-=128;
        return -(sinCos[t]);    //  Values are mirrored just negative so we just nagate
    }
    return sinCos[t];
}

float LUT::Lcos(Brad angle){return Lsin(angle+64u);}

float LUT::Ltan(Brad angle)
{
    if(angle > (unsigned char)128)
    {
        angle-=(unsigned char)128;
        return -(tanTable[angle.getAngle()]);
    }
    return tanTable[angle.getAngle()];
}

/// Interpolated Trig functions
//  CAUTION will not be accurate...
float LUT::LIsin(float angle)
{
    angle = NumberUtility::wrapValue(angle,255.0f);
    float x1 = floor(angle*1000*ONE_OVER_PI);
    float y1 = Lsin(x1);
    float y2 = Lsin(x1+1);
    return y1 + (y2-y1)*(angle*1000/PI-x1);
}

float LUT::LIcos(float angle)
{
    angle = NumberUtility::wrapValue(angle,255.0f);
    float x1 = floor(angle*1000*ONE_OVER_PI);
    float y1 = Lcos(x1);
    float y2 = Lcos(x1+1);
    return y1 + (y2-y1)*(angle*1000/PI-x1);
}

float LUT::LItan(float angle)
{
    angle = NumberUtility::wrapValue(angle,255.0f);
    float x1 = floor(angle*1000*ONE_OVER_PI);
    float y1 = Ltan(x1);
    float y2 = Ltan(x1+1);
    return y1 + (y2-y1)*(angle*1000/PI-x1);
}

uchar LUT::degreeToBrad(float angle)
{
    angle = NumberUtility::wrapValue(angle,359.0f);
    #ifdef PENJIN_FIXED
        return fixedpoint::fix2int(angle*32*POINT_ZERO_TWO_TWO);
    #else
        return angle*32*POINT_ZERO_TWO_TWO;
    #endif
}

uchar LUT::radianToBrad(CRfloat angle)
{
    return (degreeToBrad(angle*FIXED_PI*POINT_ZERO_ZERO_FIVE_FIVE));
}

float LUT::bradToDegree(CRuchar angle)
{
    return angle*45*POINT_ZERO_THREE_ONE;
}

float LUT::bradToRadian(CRuchar angle)
{
    return bradToDegree(angle)*180*ONE_OVER_PI;
}
