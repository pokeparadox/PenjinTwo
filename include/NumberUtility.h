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
#ifndef NUMBERUTILITY_H_INCLUDED
#define NUMBERUTILITY_H_INCLUDED

#include "PenjinTypes.h"

#ifndef M_PI
    #define M_PI 3.141592653f
#endif
namespace NumberUtility
{
    /// Analysis

#ifdef PENJIN_FIXED
    Fixed linearInterpolate(CRint x, CRint y, CRFixed step);
#else
    float linearInterpolate(CRint x, CRint y, CRfloat step);
#endif

    int digitSum(CRuint value);
    double fact(CRuint value);  // Returns the factorial of a given value: x! (limit is 170)
    bool isEven(CRint value);
    bool isMultiple(CRint x,CRint y);
    bool isOdd(CRint value);
    bool isPowerOfTwo(CRint x);
    bool isPrime(CRuint value);
    template <class T>
    T limit(const T& x, const T& minV, const T& maxV){return min( maxV, max(minV,x));}
    int nextPowerOfTwo(CRint x);
    template <class T>
    int sign(const T& value); // Signum function, returns the sign of a number (-1 for negative numbers, 1 for positive ones, 0 for 0)
    template <class T>
    T makePositive(const T& value); //  force a positive value
    template <class T>
    T makeNegative(const T& value); //  force a negative value

    //int wrapValue(int value, CRint limit);
    template <class T>
    T wrapValue(T val,const T& limit)
    {
    //    	We need to keep going until it is within the required range.
        while(val < 0 || val >limit)
        {
    //        	We can't have it less than 0, as it causes problems.
            if(val < 0)
            {
    //             compensate upwards
                val += limit;
            }
    //        	We can't have it more than the limit either
            else if(val > limit)
            {
    //            	compensate downwards
                val -= limit;
            }
        }
        return val;
    }

    /// Angles
    float degToRad(CRfloat a);
    float radToDeg(CRfloat a);

    /// Statistics
    template <class T, int length>
    T getGreatest(const T (&arr)[length]); // Returns the greatest number in an array
    template <class T, int length>
    int getGreatestIndex(const T (&arr)[length]); // Returns the index of the greatest number in an array
    template <class T, int length>
    bool isGreatest(const T (&arr)[length], CRuint index); // Checks if the supplied element is the greatest in an array of numbers
    template <class T, int length>
    T getLowest(const T (&arr)[length]); // Returns the lowest number in an array
    template <class T, int length>
    int getLowestIndex(const T (&arr)[length]); // Returns the index of the lowest number in an array
    template <class T, int length>
    bool isLowest(const T (&arr)[length], CRuint index); // Checks if the supplied element is the lowest in an array of numbers

    /// Arrays
    template <class T, size_t length>
    size_t getSize(const T (&arr)[length]){return length;} // Get the size of any array (array type must not have private data members)
    template <class T, int length>
    void insert(T (&arr)[length], CRint pos, T value); // Inserst a value at a position in an array - make sure the array is already big enough to hold the new value
    template <class T, int length>
    void sort(const T (&arr)[length], int (&sortIndex)[length], CRbool ascending); // Returns an array containing the indices of the elements sorted - NOT optimized for speed
};

#include "NumberUtility.inl"

#endif // NUMBERUTILITY_H_INCLUDED
