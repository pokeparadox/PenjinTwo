/*
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
*/#ifndef VECTOR1D_H
#define VECTOR1D_H
#include "Object.h"
#include <limits>

namespace Penjin
{
    template <typename T>
    class Vector1d : public Object
    {
        public:
            /** Default constructor */
            Vector1d() : x(0){;}
            Vector1d(const T& xVal) : x(xVal){;}
            Vector1d(const Vector1d& v) : x(v.x){;}

            /** Default destructor */
            virtual ~Vector1d(){;}


            void setX(const T& v)               {x=v;}
            T getX()const                       {return x;}

            virtual T length()const         {return (T)x;}
            virtual T lengthSquared()const  {return (T)(x*x);}
            virtual Vector1d unit()const        {return Vector1d(1);}
            virtual void normalise()
            {
                T len = length();
                if(len == 0 || len <= std::numeric_limits<float>::max())
                    x = 1;
                else
                    x *= len;
            }

            virtual bool equals(const Vector1d& v){return (this->x == v.x);}

        //protected:
            T x;
    };
}
#endif // VECTOR1D_H
