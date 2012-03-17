/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of PenjinTwo.

	PenjinTwo is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	PenjinTwo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with PenjinTwo.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KEYMAPPER_H
#define KEYMAPPER_H

#include "KeyMapKey.h"
#include "KeyMapMouseButton.h"
#include "KeyMapMouseAxis.h"
#include "KeyMapJoyButton.h"
#include "KeyMapJoyAxis.h"
#include "KeyMapDigitalJoyAxis.h"
#include "KeyMapHat.h"

#include "Errors.h"
#include "IniFile.h"
//using Penjin::ERRORS;
#include <vector>
namespace Penjin
{
    class KeyMapper : public IniFile
    {
        public:
            KeyMapper();
            virtual ~KeyMapper();

            size_t size()const{return keys.size();}
            KeyMap* getKeyMap(const CRuint mapping){return keys[mapping];}
            KeyMap* getKeyMap(const SIMPLEJOY_MAP& key);    //  Returns the keymap for this Command


            virtual Penjin::ERRORS load(CRstring filename);    //  Save and load the actual mapping
            Penjin::ERRORS load(const vector<string>& lines);
            virtual Penjin::ERRORS save(CRstring filename);

            void loadDefaultMap(){defaultMap();}
            std::vector <KeyMap*> keys;
            void clearKeys();
        private:
            // Disabled to prevent double freed pointers.
            KeyMapper(const KeyMapper& BlingRef);
            KeyMapper& operator=(const KeyMapper& BlingRef);
            Penjin::ERRORS mapMouse(CRuchar id);
            Penjin::ERRORS mapJoy(CRuchar id);
            Penjin::ERRORS mapKey(CRuchar id);
            Penjin::ERRORS mapWii(CRuchar id);
            Penjin::ERRORS mapWiiClassic(CRuchar id);
            Penjin::ERRORS mapWiitar(CRuchar id);
            void defaultMap();
            void applyMapping();
    };
}
#endif // KEYMAPPER_H
