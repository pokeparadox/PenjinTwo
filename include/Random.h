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
#ifndef RANDOM_H
#define RANDOM_H

/*
Pirate Games
Random number class
by Kevin Winfield-Pantoja
*/


#include <ctime>
#include <cstdlib>
#include "PenjinTypes.h"
#include "Object.h"
#include "Singleton.h"

namespace Penjin
{
    /*namespace Random
    {
        void setMax(CRint max);
        void setMin(CRint min);
        void setLimits(CRint min,CRint max);

        int nextInt();		//	get the next random int
        float nextFloat();	//	get the next float
        double nextDouble();//	get the next double
        Fixed nextFixed();
        bool nextBool();	//	random deterministic choice

        /// quick random numbers without setting limits
        float nextFloat(CRint min, CRint max);
        Fixed nextFixed(CRint min, CRint max);
        int nextInt(CRint min, CRint max);
        double nextDouble(CRint min, CRint max);

        void setSeed(CRint seed);
        int getSeed();
        int randSeed();			//	Also returns the seed value
    }*/

    class Random : public Object
    {
        public:
            Random();

            Random(CRint min, CRint max);

            int randSeed();			//	Also returns the seed value
            void setSeed(CRint s){seed = s;srand(s);}
            int getSeed() const {return seed;}

            void setMax(CRint max);
            void setMin(CRint min);
            void setLimits(CRint min,CRint max);

            bool nextBool();	//	random deterministic choice
            int nextInt();		//	get the next random int
            float nextFloat();	//	get the next float
            double nextDouble();//	get the next double
            Fixed nextFixed();  //  geet next 16.16 fixed point number

            /// quick random numbers without setting limits
            float nextFloat(CRint min, CRint max);
            Fixed nextFixed(CRint min, CRint max);
            int nextInt(CRint min, CRint max);
            double nextDouble(CRint min, CRint max);

        private:
            int seed;
            int min;
            int max;
    };

    typedef Singleton<Random> RandMan;
}
#endif	// RANDOM_H

