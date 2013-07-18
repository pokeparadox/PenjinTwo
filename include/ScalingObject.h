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
*   \file ScalingObject is a class to add scaling
*   \author Kevin Winfield-Pantoja
*/

#ifndef SCALINGOBJECT_H
#define SCALINGOBJECT_H

#include "Object.h"
#include "Vector2d.h"

namespace Penjin
{
    class ScalingObject : public Object
    {
        public:
            /** Default constructor */
            ScalingObject();
            /** Default destructor */
            virtual ~ScalingObject();

            void setScaleX(const float& s){scale.x = s;}
            void setScaleY(const float& s){scale.y = s;}

            void setScale(const float& s){scale.x = scale.y = s;}
            template <class T>
            void setScale(const T& s){scale.setX(s.x);scale.setY(s.y);}
            template <class T>
            void setCentreOfScaling(const T& centre){centreOfScaling.x = centre.x; centreOfScaling.y = centre.y;}
            Vector2d<float> getScale(){return scale;}
            Vector2d<int> getCentreOfScaling(){return centreOfScaling;}
        protected:
            Vector2d<float> scale;
            Vector2d<int> centreOfScaling;
    };
}

#endif // SCALINGOBJECT_H
