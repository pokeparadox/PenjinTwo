#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

/*
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
*/
/***************************************************************************************************
*   \file Vector3d is a 3D vector
*   \author Kevin Winfield-Pantoja
*/
#include "Vector2d.h"

namespace Penjin
{
    template <typename T>
    class Vector3d : public Vector2d<T>
    {
        public:
            /** Default constructor */
            Vector3d() : z(0){;}
            Vector3d(const T& x, const T& y, const T& z) : z(z) {this->x = x; this->y = y;}
            Vector3d(const Vector1d<T> & v) : z(0) {this->x = v.x;this->y = 0;}
            Vector3d(const Vector2d<T> & v) : z(0) {this->x = v.x;this->y = v.y;}
            Vector3d(const Vector3d<T> & v) : z(v.z) {this->x = v.x;this->y = v.y;}

            /** Default destructor */
            virtual ~Vector3d(){;}

            void setZ(const T& v){z=v;}
            T getZ()const{return z;}

            Vector3d<T> normalisedCross(const Vector3d<T> & v)
            {
                Vector3d<T> out = cross(v);
                out.normalise();
                return out;
            }

            Vector3d<T> cross(const Vector3d<T> & v){return Vector3d<T>(this->y*v.z - z*v.y, z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);}

            virtual T dot(const Vector3d<T>& v)const{return (this->x * v.x + this->y * v.y + z * v.z);}
            virtual T lengthSquared()const          {return (this->x*this->x + this->y*this->y + z*z);}
            virtual T length()const                 {return sqrt(lengthSquared());}
            virtual Vector3d<T> unit()
            {
                float len = length();
                if(len == 0)
                    return Vector3d<T> (0,1,0);

                float temp = 1/len;
                return Vector3d<T>(this->x*temp,this->y*temp, this->z*temp);
            }

            T z;
    };
}
#endif // VECTOR3D_H_INCLUDED
