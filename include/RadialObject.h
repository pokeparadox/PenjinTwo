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
*/#ifndef RADIALOBJECT_H
#define RADIALOBJECT_H

#include "DimensionObject.h"

namespace Penjin
{
    class RadialObject : public DimensionObject
    {
        public:
            /** Default constructor */
            RadialObject();
            /** Default destructor */
            virtual ~RadialObject();

            virtual void setRadius(unsigned int r);
            unsigned int getRadius();
            virtual void setRadius2(unsigned int r2);
            unsigned int getRadius2();
            virtual void setRadii(Vector2d<unsigned int> radii);
            Vector2d<unsigned int> getRadii()
            {
                return getDimensions()*0.5f;
            }

            virtual void setDiameter(unsigned int d);
            unsigned int getDiameter();
            virtual void setDiameter2(unsigned int d2);
            unsigned int getDiameter2();
            virtual void setDiameters(Vector2d<unsigned int> diameters);
            Vector2d<unsigned int> getDiameters()
            {
                return getDimensions();
            }

        protected:
        private:
    };
}
#endif // PENJINRADIALOBJECT_H
