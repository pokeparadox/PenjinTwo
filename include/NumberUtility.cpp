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
#include "NumberUtility.h"

///----------------------
/// Analysis
///----------------------

#ifdef PENJIN_FIXED
    Fixed NumberUtility::linearInterpolate(CRint x, CRint y, CRFixed step)
    {
        Fixed temp = x + step;
        if(temp < y)
            return temp;
        return Fixed(y);
    }
#else
    float NumberUtility::linearInterpolate(CRint x, CRint y, CRfloat step)
    {
        float temp = x + step;
        if(temp < y)
            return temp;
        return (float)y;
    }
#endif

int NumberUtility::digitSum(CRuint value)
{
    int result = 0;
    int temp = value;
    while (temp != 0)
        {
            result += temp % 10;
            temp /= 10;
        }
    return result;
}

double NumberUtility::fact(CRuint value)
{
    double result=1;
    for (int I=value; I > 0; --I)
    {
        result *= I;
    }
    return result;
}

bool NumberUtility::isEven(CRint value){return (value%2 == 0);}

bool NumberUtility::isMultiple(CRint x,CRint y){return (x%y == 0);}

bool NumberUtility::isOdd(CRint value){return !(value%2 ==0);}

bool NumberUtility::isPowerOfTwo(CRint x){return ((x != 0) && !(x & (x - 1)));}

int NumberUtility::nextPowerOfTwo(CRint x)
{
    double logbase2 = log(x) / log(2);
    return (int)round(pow(2,ceil(logbase2)));
}

bool NumberUtility::isPrime(CRuint value)
{
    for (int I = 2; I <= int(value/2); I++)
        if (value % I == 0)
            return false;
    return true;
}

///----------------------
/// Angles
///----------------------

float NumberUtility::degToRad(CRfloat a)
{
    return a * 0.017453292f;
}

float NumberUtility::radToDeg(CRfloat a)
{
    return a * 57.29578f;
}
