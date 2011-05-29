/**
    \section LICENSE
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
/**
  * \file A class that decribes the width and height of an object
  * \author Kevin Winfield-Pantoja
  */
#ifndef DIMENSIONOBJECT_H
#define DIMENSIONOBJECT_H
#include "Object.h"
#include "Vector2d.h"

using Penjin::Object;
using Penjin::Vector2d;

namespace Penjin
{
    class DimensionObject : public Object
    {
        public:
            /** Default constructor */
            DimensionObject();
            /** Default destructor */
            virtual ~DimensionObject();

            // Setting methods
            /** \brief Set the width and height of an object.
             * \param dims : the dimensions to set which must have x and y components.
             */
            template <class T>
            void setDimensions(const T& dims){dimensions.x=dims.x;dimensions.y=dims.y;}
            /** \brief Set the width and height of an object.
             * \param x : the width.
             * \param y : the height.
             */
            template <class T>
            void setDimensions(const T& x, const T& y){dimensions.x=x;dimensions.y=y;}
            /** \brief Set the width of an object.
             * \param w : the width to set, which must be numerical.
             */
            template <class T>
            void setWidth(const T& w){dimensions.x=w;}
            /** \brief Set the height of an object.
             * \param h : the height to set, which must be numerical.
             */
            template <class T>
            void setHeight(const T& h){dimensions.y=h;}

            // Getting methods
            virtual Vector2d<int> getDimensions()const;
            virtual int getWidth()const;
            virtual int getHeight()const;

        protected:
            Vector2d<int> dimensions;
    };
}
#endif // DIMENSIONOBJECT_H
