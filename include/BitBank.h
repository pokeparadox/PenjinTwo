/**
	\section LICENSE
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
/***************************************************************************************************
*   \file BitBank is Easy access storage to set bits.
*   \author Kevin Winfield-Pantoja
*/

#ifndef BITBANK_H
#define BITBANK_H
#include "PenjinTypes.h"
#include <limits.h>
namespace Penjin
{
    template <typename T>
    class BitBank : public Object
    {
        public:
            /** Default constructor */
            BitBank()       //  Will use max bits available for type
            {
                activeBits = countBits();
            }
            BitBank(CRuchar numBits)   //  Will try to use specified number of bits
            {
                unsigned int t = countBits();
                if(numBits <= t)
                    activeBits = numBits;
                else
                    activeBits = t;
            }
            /** Default destructor */
            virtual ~BitBank();

            // Clear all bits
            void clear()
            {
                bits = 0;
            }

            void clear(const unsigned char& bit)
            {
                bits &= ~(1 << bit);
            }

            void set(const unsigned char& bit)
            {
                bits |= 1 << bit;
            }

            // toggles the bit at
            void toggle(const unsigned char& bit)
            {
                bits ^= 1 << bit;
            }

            //  Check a bit true is 1, false is 0
            bool operator[](const unsigned char& bit)
            {
                return at(bit);
            }
            bool at(const unsigned char& bit)
            {
                if(bit < size())
                    return (bool)(bits & (1 << bit));
                return false;
            }

            unsigned char size(){return activeBits;}
        protected:
        private:
            unsigned int countBits()
            {
                return (sizeof(T) * CHAR_BIT);
            }

            T bits;
            unsigned char activeBits;   // number of available bits.
    };
}

#endif // BITBANK_H
