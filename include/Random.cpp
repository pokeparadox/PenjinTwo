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
#include "Random.h"
using Penjin::Random;
/*namespace Penjin
{
    namespace Random
    {
        int min = 0;
        int max = 1;
        int seed = randSeed();
    }
}*/
Penjin::Random::Random()
{

}

Penjin::Random::Random(const int & min, const int& max)
{
   this->min = min;
   this->max = max;
}

int Penjin::Random::randSeed()	//	seed the random number generator
{
    int seed = static_cast<int>(time(0));
    srand(seed);
    return seed;
}

/*int Penjin::Random::getSeed()const
{
    return seed;
}*/

bool Penjin::Random::nextBool()
{
    return(rand()%2 == 0);
}

/*Fixed Penjin::Random::nextFixed()
{
    int range = max-min;
    return (min + Fixed(range * rand() /(RAND_MAX + 1.0f)));
}*/
/*float Penjin::Random::nextFloat()
{
	float range = max - min;
	return (min + float(range * rand() / (RAND_MAX + 1.0f )));
}*/

/*double Penjin::Random::nextDouble()
{
	double range = max - min;
	return (min + double(range * rand() / (RAND_MAX + 1.0)));
}*/

//int Penjin::Random::nextInt(){return (min + rand() % (max - min +1));}

float Penjin::Random::nextFloat(CRint min, CRint max)
{
	float range = max - min;
	return (min + float(range * rand() / (RAND_MAX + 1.0f )));
}

Fixed Penjin::Random::nextFixed(CRint min, CRint max)
{
    int range = max-min;
    return (min + Fixed(range * rand() /(RAND_MAX + 1.0f)));
}

double Penjin::Random::nextDouble(CRint min, CRint max)
{
	double range = max - min;
	return (min + double(range * rand() / (RAND_MAX + 1.0)));
}

int Penjin::Random::nextInt(CRint min, CRint max){return (min + rand() % (max - min +1));}

//void Penjin::Random::setSeed(CRint s){srand(s);seed=s;}
void Penjin::Random::setLimits(CRint min,CRint max){setMin(min);setMax(max);}
void Penjin::Random::setMax(CRint m){max = m;}
void Penjin::Random::setMin(CRint m){min = m;}

/// random class
//using Penjin::RandomClass;

//Random::Random(CRint min, CRint max){this->min = min;this->max = max;}
//void Random::setMax(CRint max){this->max = max;}
//void Random::setMin(CRint min){this->min = min;}
//void Random::setLimits(CRint min,CRint max){this->min = min;this->max = max;}

int Random::nextInt(){return nextInt(min,max);}		//	get the next random int
float Random::nextFloat(){return nextFloat(min,max);}	//	get the next float
double Random::nextDouble(){return nextDouble(min,max);}//	get the next double
Fixed Random::nextFixed(){return nextFixed(min,max);}
