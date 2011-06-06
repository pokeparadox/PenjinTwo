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
#include "KeyMapMouseButton.h"

KeyMapMouseButton::KeyMapMouseButton()
{
    //ctor
    device = DEV_MOUSE_BUTTON;
    mouseButton = SDL_MOUSE_NONE;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapMouseButton::~KeyMapMouseButton()
{
    //dtor
}

KeyMapMouseButton::KeyMapMouseButton(CRuchar b,CRstring SJ,CRuchar id, CRuint p)
{
    setMouseButton(b);
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_MOUSE_BUTTON;
    player = p;
}

void KeyMapMouseButton::setMouseButton(CRuchar b)
{
    switch(b)
    {
        case 0:     mouseButton = SDL_MOUSE_LEFT;   break;
        case 1:     mouseButton = SDL_MOUSE_CENTRE; break;
        case 2:     mouseButton = SDL_MOUSE_RIGHT;  break;
        default:    mouseButton = SDL_MOUSE_NONE;   break;
    }
}

bool KeyMapMouseButton::isMapValid()
{
    return (target != SJ_UNMAPPED && mouseButton != SDL_MOUSE_NONE && player != 0);
}
