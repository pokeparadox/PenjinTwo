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
#ifndef KEYMAPJOYBUTTON_H
#define KEYMAPJOYBUTTON_H

#include "KeyMap.h"
using Penjin::KeyMap;
using namespace Penjin::KeyMappings;

class KeyMapJoyButton : public KeyMap
{
    public:
        KeyMapJoyButton();
        KeyMapJoyButton(CRint button,CRstring SJ,CRuchar devID, CRuint player = 1);
        virtual ~KeyMapJoyButton();

        void setBind(CRint b,const SIMPLEJOY_MAP& t,CRuchar devID){joyButton=b;target=t;deviceID = devID;}
        int getButton()const{return joyButton;}
        virtual bool isMapValid();
    private:
        int joyButton;
};

#endif // KEYMAPJOYBUTTON_H
