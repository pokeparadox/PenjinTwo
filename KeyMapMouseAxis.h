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
#ifndef KEYMAPMOUSEAXIS_H
#define KEYMAPMOUSEAXIS_H

#include "KeyMap.h"

using Penjin::KeyMap;
using namespace Penjin::KeyMappings;

namespace MouseAxes
{
    enum SDL_MOUSE_AXES
    {
        SDL_MOUSE_NONE=-1,
        SDL_MOUSE_X,
        SDL_MOUSE_Y
        //SDL_MOUSE_WHEEL,
    };
}
using namespace MouseAxes;

class KeyMapMouseAxis : public KeyMap
{
    public:
        KeyMapMouseAxis();
        KeyMapMouseAxis(CRuchar axis,CRstring SJ,CRuchar devID, CRuint player = 1);
        virtual ~KeyMapMouseAxis();

        void setBind(CRuchar a,const SIMPLEJOY_MAP& t,CRuchar devID, CRuint player = 1){mouseAxis=a;target=t;deviceID = devID;}
        uchar getAxis()const{return mouseAxis;}

        virtual bool isMapValid();
    private:
        uchar mouseAxis;

};

#endif // KEYMAPMOUSEAXIS_H
