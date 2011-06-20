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
#ifndef KEYMAPDIGITALJOYAXIS_H
#define KEYMAPDIGITALJOYAXIS_H

#include "KeyMap.h"
using Penjin::KeyMap;
using namespace Penjin::KeyMappings;

class KeyMapDigitalJoyAxis : public KeyMap
{
    public:
        KeyMapDigitalJoyAxis();
        virtual ~KeyMapDigitalJoyAxis();

        KeyMapDigitalJoyAxis(CRstring SJ,CRint axis,CRint triggerVal,CRuchar devID, CRuint player = 1);

        void setBind(const SIMPLEJOY_MAP& t,CRint a,CRint triggerVal,CRuchar devID, CRuint player = 1){axis=a;target=t;trigger=triggerVal;deviceID = devID;}
        int getAxis()const{return axis;}
        int getTrigger()const{return trigger;}

        virtual bool isMapValid();
    private:
        int axis;
        int trigger;
};

#endif // KEYMAPDIGITALJOYAXIS_H
