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
//----------------------
// template functions implementation
//----------------------
///----------------------
/// Sign
///----------------------

template <class T>
int NumberUtility::sign(const T& value)
{
    return (value > 0) - (0 > value);
}

template <class T>
T NumberUtility::makePositive(const T& value)
{
    return abs(value);
}

template <class T>
T NumberUtility::makeNegative(const T& value)
{
    return - abs(value);
}
///----------------------
/// Statistics
///----------------------

template <class T, int length>
T NumberUtility::getGreatest(const T (&arr)[length])
{
    T result = arr[length - 1];
    for (int I = length - 2; I >= 0; --I)
    {
        if (arr[I] > result)
        {
            result = arr[I];
        }
    }
    return result;
}

template <class T, int length>
int NumberUtility::getGreatestIndex(const T (&arr)[length])
{
    int result = length - 1;
    for (int I = length - 2; I >= 0; --I)
    {
        if (arr[I] > arr[result])
        {
            result = I;
        }
    }
    return result;
}

template <class T, int length>
bool NumberUtility::isGreatest(const T (&arr)[length], CRuint index)
{
    for (int I = length - 1; I >= 0; --I)
    {
        if (arr[I] > arr[index])
        {
            return false;
        }
    }
    return true;
}

template <class T, int length>
T NumberUtility::getLowest(const T (&arr)[length])
{
    T result = arr[length - 1];
    for (int I = length - 2; I >= 0; --I)
    {
        if (arr[I] < result)
        {
            result = arr[I];
        }
    }
    return result;
}

template <class T, int length>
int NumberUtility::getLowestIndex(const T (&arr)[length])
{
    int result = length - 1;
    for (int I = length - 2; I >= 0; --I)
    {
        if (arr[I] < arr[result])
        {
            result = I;
        }
    }
    return result;
}

template <class T, int length>
bool NumberUtility::isLowest(const T (&arr)[length], CRuint index)
{
    for (int I = length - 1; I >= 0; --I)
    {
        if (arr[I] < arr[index])
        {
            return false;
        }
    }
    return true;
}

///----------------------
/// Arrays
///----------------------

template <class T, int length>
void NumberUtility::insert(T (&arr)[length], CRint pos, T value)
{
    // Shift all elements after the insert pos one position up
    for (int I = length-2; I >= pos; I--)
    {
        arr[I+1] = arr[I];
    }
    arr[pos] = value;
}

template <class T, int length>
void NumberUtility::sort(const T (&arr)[length], int (&sortIndex)[length], CRbool ascending)
{
    int counter=0;
    for (int I = length-1; I >= 0; --I) {
        // Go through all elements already added to the IndexArray
        for (int K = counter; K >= 0; --K) {
            // If it is the last item of the list or
            // if the element is smaller/bigger
            if ((K == 0) || (ascending && (arr[I] > arr[sortIndex[K-1]])) || (not ascending && (arr[I] < arr[sortIndex[K-1]])) ) {
                // Insert index of element into the array
                insert(sortIndex,K,I);
                counter++;
                break;
            }
        }
    }
}
