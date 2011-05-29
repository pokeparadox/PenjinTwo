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
#ifndef PENJINFIXEDFUNC_H_INCLUDED
#define PENJINFIXEDFUNC_H_INCLUDED
/*
AUTHOR: Kevin Winfield-Pantoja
DESCRIPTION: helper functions to Trenki's Fixed point library.
*/

#include "trenki/fixed_class.h"
#include "trenki/fixed_func.h"
#include "trenki/vector_math.h"
namespace fixedpoint
{
    template <int p>
    int fix2int(int32_t f){return (f << p);}

    template <int p>
    int fix2int(fixed_point<p> f){return (f.intValue << p);}

    template <int p>
    vmath::vec2<int> fix2int(vmath::vec2<fixedpoint::fixed_point<p> > f){return vmath::vec2<int>(fix2int(f.x),fix2int(f.y));}

    template <int p>
    vmath::vec3<int> fix2int(vmath::vec3<fixedpoint::fixed_point<p> > f){return vmath::vec3<int>(fix2int(f.x),fix2int(f.y),fix2int(f.z));}

    template <int p>
    vmath::vec2<float> fix2float(vmath::vec2<fixedpoint::fixed_point<p> > f){return vmath::vec2<float>(fix2float(f.x),fix2float(f.y));}

    template <int p>
    vmath::vec3<float> fix2float(vmath::vec3<fixedpoint::fixed_point<p> > f){return vmath::vec3<float>(fix2float(f.x),fix2float(f.y),fix2float(f.z));}

    template <int p>
    float fix2float(fixed_point<p> f){return (float)f.intValue / (1 << p);}

    fixed_point<16> fixsqrt16(fixed_point<16> a);
}
#endif // PENJINFIXEDFUNC_H_INCLUDED
