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
*   \file CLASS_NAME is INSERT DESCRIPTION
*   \author Kevin Winfield-Pantoja
*/

#ifndef ROTATIONOBJECT_H
#define ROTATIONOBJECT_H

#include "Object.h"
#include "Vector2d.h"

namespace Penjin
{
    class RotationObject : public Object
    {
        public:
            /** Default constructor */
            RotationObject();
            /** Default destructor */
            virtual ~RotationObject();

            void setAngle(const float& a){angle = a;}
            void setRotation(const float& a){setAngle(a);}
            float getAngle()const{return angle;}

            template <class T>
            void setCentreOfRotation(const T& c){centreOfRotation.x = c.x;centreOfRotation.y = c.y;}
            Vector2d<int> getCentreOfRotation()const{return centreOfRotation;}

        protected:
            float angle;                    //  angle in degs to rotate
            Vector2d<int> centreOfRotation; //  The point where the rotation is centred
    };
}
#endif // ROTATIONOBJECT_H
