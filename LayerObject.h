/*
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
  * \file LayerObject handles layering, e.g. of windows, tile layers, etc.
  * \author Kevin Winfield-Pantoja
  */
#ifndef LAYEROBJECT_H
#define LAYEROBJECT_H

#include "RenderObject.h"
#include "Rectangle.h"

namespace Penjin
{
    class LayerObject : public Rectangle
    {
        public:
            /** Default constructor */
            LayerObject();
            /** Default destructor */
            virtual ~LayerObject();

            /** \brief Sets which layer this object occupies.
             * \param l : the layer.
             */
            void setLayer(const int&l);

            /** \brief Gets which layer this object occupies.
             * \return the layer.
             */
            int getLayer();

        protected:
            int layer;
    };
}
#endif // LAYEROBJECT_H
