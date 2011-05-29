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
#ifndef KEYMAPMOUSEBUTTON_H
#define KEYMAPMOUSEBUTTON_H

#include "KeyMap.h"
using Penjin::KeyMap;
using namespace Penjin::KeyMappings;

namespace MouseButtons
{
    enum SDL_MOUSE_BUTTONS
    {
        SDL_MOUSE_NONE,
        SDL_MOUSE_LEFT,
        SDL_MOUSE_CENTRE,
        SDL_MOUSE_RIGHT
    };
}
using namespace MouseButtons;

class KeyMapMouseButton : public KeyMap
{
    public:
        KeyMapMouseButton();
        KeyMapMouseButton(CRuchar button,CRstring SJ,CRuchar devID, CRuint player = 1);
        virtual ~KeyMapMouseButton();

        void setBind(const SDL_MOUSE_BUTTONS& b,const SIMPLEJOY_MAP& t,CRuchar devID, CRuint player = 1){mouseButton=b;target=t;deviceID = devID;}
        SDL_MOUSE_BUTTONS getButton()const{return mouseButton;}

        virtual bool isMapValid();

    private:
        void setMouseButton(CRuchar button);
        SDL_MOUSE_BUTTONS mouseButton;
};

#endif // KEYMAPMOUSEBUTTON_H
