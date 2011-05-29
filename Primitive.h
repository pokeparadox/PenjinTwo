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
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "GFX.h"
#include "Colour.h"
#include "RenderObject.h"
/**
  * \file Primitive class is a base for gneral geometric shapes.
  * \author Kevin Winfield-Pantoja
  */
namespace Penjin
{
    class Primitive : public Colour, public RenderObject
    {
        public:
            /** Default constructor */
            Primitive();
            /** Default destructor */
            virtual ~Primitive();

            /** \brief Sets the drawing/line width of the renderer used to draw this Primitive.
             * \param w : The width in pixels (-1 signifies a filled Primitive)
             */
            void setDrawWidth(const int& w);

        protected:
            int drawWidth;  /**< The renderer line width to use in drawing this Primitive. */
    };
}
#endif // PRIMITIVE_H
