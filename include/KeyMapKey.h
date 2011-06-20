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
#ifndef KEYMAPKEY_H
#define KEYMAPKEY_H

#include "KeyMap.h"
using Penjin::KeyMap;
using namespace Penjin::KeyMappings;

class KeyMapKey : public KeyMap
{
    public:
        KeyMapKey();
        KeyMapKey(CRstring SJ,CRstring k,CRuchar devID, CRuint player = 1){setKey(k);setSJMap(SJ);setDeviceID(devID);device = DEV_KEYBOARD;this->player = player;}
        KeyMapKey(CRstring k);
        #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            KeyMapKey(__u16 k);
        #else
            KeyMapKey(SDLKey k);
        #endif
        virtual ~KeyMapKey();

        #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            void setBind(const __u16& k,const SIMPLEJOY_MAP& t,CRuchar devID){key=k;target=t;deviceID = devID;}
            __u16 getKey()const{return key;}
        #else
            void setBind(const SDLKey& k,const SIMPLEJOY_MAP& t,CRuchar devID){key=k;target=t;deviceID = devID;}
            SDLKey getKey()const{return key;}
        #endif

        virtual bool isMapValid();

    private:
        void setKey(CRstring key);
        #if defined(PLATFORM_PANDORA) && !defined(PENJIN_SDL_INPUT)
        // && (defined(PENJIN_ES) || defined(PENJIN_ES2))
            __u16 key;
        #else
            SDLKey key;
        #endif
};

#endif // KEYMAPKEY_H
