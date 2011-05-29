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
#include "KeyMapHat.h"

KeyMapHat::KeyMapHat()
{
    //ctor
    device = DEV_JOYSTICK_HAT;
    direction = SDL_HAT_CENTERED;
    target = SJ_UNMAPPED;
    setDeviceID(0);
}

KeyMapHat::~KeyMapHat()
{
    //dtor
}

KeyMapHat::KeyMapHat(const Uint8& d,CRstring SJ,CRuchar id, CRuint p)
{
    direction=d;
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_JOYSTICK_HAT;
    player = p;
}

KeyMapHat::KeyMapHat(CRstring d,CRstring SJ,CRuchar id, CRuint p)
{
    setDirection(d);
    setSJMap(SJ);
    setDeviceID(id);
    device = DEV_JOYSTICK_HAT;
    player = p;
}

void KeyMapHat::setDirection(CRstring dir)
{
    if(dir == "UP")
        direction = SDL_HAT_UP;
    else if(dir == "DOWN")
        direction = SDL_HAT_DOWN;
    else if(dir == "LEFT")
        direction = SDL_HAT_LEFT;
    else if(dir == "RIGHT")
        direction = SDL_HAT_RIGHT;
    else if(dir == "UPLEFT")
        direction = SDL_HAT_LEFTUP;
    else if(dir == "UPRIGHT")
        direction = SDL_HAT_RIGHTUP;
    else if(dir == "DOWNLEFT")
        direction = SDL_HAT_LEFTDOWN;
    else if(dir == "DOWNRIGHT")
        direction = SDL_HAT_RIGHTDOWN;
    else
        direction = SDL_HAT_CENTERED;
}

bool KeyMapHat::isMapValid()
{
    return (target != SJ_UNMAPPED && direction != SDL_HAT_CENTERED && player != 0);
}
