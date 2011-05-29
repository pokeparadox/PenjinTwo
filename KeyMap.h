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
#ifndef KEYMAP_H
#define KEYMAP_H

#include "PenjinTypes.h"
#include "Object.h"
#if defined(PLATFORM_PANDORA)
#if !defined(PENJIN_SDL_INPUT)
// && (defined(PENJIN_ES) || defined(PENJIN_ES2))
    #include <linux/input.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdio.h>
#endif
#endif
#include <SDL/SDL.h>
#include <string>
using std::string;

namespace Penjin
{
    namespace KeyMappings
    {
        /// Device types
        enum KEY_MAP_DEVICE
        {
            DEV_KEYBOARD,
            DEV_MOUSE_BUTTON,
            DEV_MOUSE_AXIS,
            DEV_DIGITAL_JOYSTICK_AXIS,
            DEV_JOYSTICK_AXIS,
            DEV_JOYSTICK_BUTTON,
            DEV_JOYSTICK_HAT,
            DEV_WII_REMOTE,
            DEV_WII_CLASSIC,
            DEV_WII_GUITAR,
            DEV_UNKNOWN
        };
        /// SimpleJoy Mappings
        enum SIMPLEJOY_MAP
        {
            SJ_UP,
            SJ_DOWN,
            SJ_LEFT,
            SJ_RIGHT,
            SJ_UPLEFT,
            SJ_UPRIGHT,
            SJ_DOWNLEFT,
            SJ_DOWNRIGHT,
            SJ_A,
            SJ_B,
            SJ_X,
            SJ_Y,
            SJ_L,
            SJ_R,
            SJ_VOLUP,
            SJ_VOLDOWN,
            SJ_START,
            SJ_SELECT,
            SJ_CLICK,
            SJ_LID,
            SJ_LEFTSTICK_X,
            SJ_LEFTSTICK_Y,
            SJ_RIGHTSTICK_X,
            SJ_RIGHTSTICK_Y,
            SJ_MOUSE_X,
            SJ_MOUSE_Y,
            SJ_MOUSE_LEFT,
            SJ_MOUSE_CENTRE,
            SJ_MOUSE_RIGHT,
            SJ_UNMAPPED
        };
    }

    using namespace Penjin::KeyMappings;
    class KeyMap : public Object
    {
        public:
            KeyMap();
            virtual ~KeyMap();

            void setDevice(KEY_MAP_DEVICE dev){device = dev;}
            void setDeviceID(CRuchar id){deviceID = id;}
            uchar getDeviceID()const{return deviceID;}
            KEY_MAP_DEVICE getDevice()const{return device;}
            SIMPLEJOY_MAP getTarget()const{return target;}
            void setPlayer(CRuint player){this->player = player;}
            uint getPlayer()const{return player;}

            virtual bool isMapValid()=0;
        protected:
            void setSJMap(string target);
            KEY_MAP_DEVICE device;      //  What type of device are we mapping?
            SIMPLEJOY_MAP target;       //  The target the mapped key will trigger.
            uchar deviceID;
            uint player;
    };
}
#endif // KEYMAP_H
