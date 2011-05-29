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
        protected:
        private:
    };
}
#endif // PENJINRADIALOBJECT_H
