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
*/#ifndef BRAD_H
#define BRAD_H

#include "Object.h"

namespace Penjin
{
    class Brad : public Object
    {
        public:
            /** Default constructor */
            Brad();
            //Brad(const Brad& b);
            Brad(const float& deg);
            Brad(const unsigned char& bradRAW);
            /** Default destructor */
            virtual ~Brad();

            void setAngleDegrees(float degrees);
            void setAngleRadians(const float& rad);
            void setAngle(Brad brad);
            void setAngle(const unsigned char& bradRAW);

            float getAngleDegrees();
            float getAngleRadians();
            // get RAW Brad angle
            unsigned char getAngle();

            // Operators
            Brad operator=(const Brad& b){setAngle(b);return *this;}
            Brad operator=(const unsigned char& b){setAngle(b);return *this;}
            Brad operator=(const float& deg){setAngleDegrees(deg);return *this;}

            bool operator==(Brad b){return(b.getAngle() == brad);}
            bool operator==(const unsigned char& b){return(brad==b);}
            bool operator==(const float& deg){return(getAngleDegrees()==deg);}

            bool operator>(Brad b){return (b.getAngle() > brad);}

            Brad operator+(Brad b)const{return Brad((unsigned char)(b.getAngle() + brad));}
            Brad operator+(const unsigned char & b)const{return Brad((unsigned char)(b + brad));}
            Brad operator+(const float & deg){return Brad((float)(deg + getAngleDegrees()));}

            Brad operator++(){brad+=1;return *this;}

            Brad operator-(Brad b)const{return Brad((unsigned char)(b.getAngle() - brad));}
            Brad operator-(const unsigned char & b)const{return Brad((unsigned char)(b - brad));}
            Brad operator-(const float & deg){return Brad((float)(deg - getAngleDegrees()));}

            Brad operator-=(Brad b){return Brad (brad -= b.getAngle());}

        private:
            unsigned char brad; // The raw uchar brad.
    };
}
#endif // BRAD_H
