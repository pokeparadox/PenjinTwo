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
#include "KeyMapper.h"
#include "StringUtility.h"
using Penjin::KeyMapper;


KeyMapper::KeyMapper()
{
    //ctor
    setFileName("config/input/default.ini");
    this->load(fileName);
}

KeyMapper::~KeyMapper()
{
    //dtor
    clearKeys();
}

void KeyMapper::clearKeys()
{
    for(int i = keys.size()-1; i>=0; --i)
    {
        if(keys[i])
            delete keys[i];
        keys[i]=NULL;
    }
    keys.clear();
}

Penjin::ERRORS KeyMapper::load(const vector<string>& lines)
{
    //parse->loadCommandList(lines);
    return Penjin::PENJIN_FUNCTION_IS_STUB;
}

Penjin::ERRORS KeyMapper::load(CRstring file)
{

    Penjin::ERRORS result = this->ConfigFile::load(file);
    if(result != PENJIN_OK)
    {
        defaultMap();
        result = PENJIN_OK;
        //return result;
    }
    return result;
}

Penjin::ERRORS KeyMapper::save(CRstring file)
{
    return Penjin::PENJIN_FUNCTION_IS_STUB;
}

void KeyMapper::defaultMap()
{
    clearKeys();
    string device;
    string ID;
    string player= "1";
#if defined(PLATFORM_PANDORA) || defined(PLATFORM_PC)
    device = "Keyboard";
    ID="0";
    setValue(device,"DeviceNumber",ID);
    setValue(device,"Player", player);
        setValue(device,"Up",       "Up");
        setValue(device,"Down",     "Down");
        setValue(device,"Left",     "Left");
        setValue(device,"Right",    "Right");
    device = "Mouse";
    setValue(device,"DeviceNumber",ID);
    setValue(device,"Player", player);
        setValue(device,"LeftButton",   "0");
        setValue(device,"MouseAxisX",        "0");
        setValue(device,"MouseAxisY",        "1");
#endif

#ifdef PLATFORM_PC
    device = "Keyboard";
        setValue(device,"A",        "x");
        setValue(device,"B",        "z");
        setValue(device,"X",        "a");
        setValue(device,"Y",        "s");
        setValue(device,"L",        "q");
        setValue(device,"R",        "w");
        setValue(device,"Select",   "RightShift");
        setValue(device,"Start",    "Return");
#elif PLATFORM_GP2X
    device = "Joystick";
    ID = "0";
    setValue(device,"DeviceNumber",ID);
    setValue(device,"Player", player);
        setValue(device,"Up",           "0");
        setValue(device,"UpLeft",       "1");
        setValue(device,"Left",         "2")
        setValue(device,"DownLeft",     "3");
        setValue(device,"Down",         "4");
        setValue(device,"DownRight",    "5");
        setValue(device,"Right",        "6");
        setValue(device,"UpRight",      "7");
        setValue(device,"Start",        "8");
        setValue(device,"Select",       "9")
        setValue(device,"L",            "10");
        setValue(device,"R",            "11");
        setValue(device,"A",            "12");
        setValue(device,"B",            "13");
        setValue(device,"X",            "14");
        setValue(device,"Y",            "15");
        setValue(device,"VolumeUp",     "16");
        setValue(device,"VolumeDown",   "17");
        setValue(device,"Click",        "18");
#elif PLATFORM_DINGOO
    device="Keyboard";
    ID="0";
    setValue(device,"Player", player);
    setValue(device,"DeviceNumber",ID);
        setValue(device, "Up",      "UP");
        setValue(device, "Down",    "Down");
        setValue(device, "Left",    "Left");
        setValue(device, "Right",   "Right");
        setValue(device, "A",       "LeftCtrl");
        setValue(device, "B",       "LeftAlt");
        setValue(device, "X",       "Space");
        setValue(device, "Y",       "LeftShift");
        setValue(device, "L",       "Tab");
        setValue(device, "R",       "Backspace");
        setValue(device, "Start",   "Return");
        setValue(device, "Select",  "Escape");
#elif PLATFORM_PANDORA
//0 TOP/X,1 RIGHT/A,2 BOTTOM/B,3 LEFT/Y,4 SELECT,5 START,6 PANDORA,7 L,8 R,9 L2,10 R2,11 HOLD
/*
 EvilDragon: Buttons are: START = LALT, SELECT = LCTRL, L = RSHIFT, R = RCTRL and on the button side:
EvilDragon: Top Button = Page Up, Lower Button = Page Down, Left Button = Prior, Right Button = Next
EvilDragon: DPad works, that's Cursor Up, Down, Left, Right.
*/
    device="Keyboard";
    ID="0";
    setValue(device,"DeviceNumber",ID);
        setValue(device, "A",       "Home");
        setValue(device, "B",       "End");
        setValue(device, "X",       "PageDown");
        setValue(device, "Y",       "PageUp");
        setValue(device, "L",       "RightShift");
        setValue(device, "R",       "RightCtrl");
        setValue(device, "Select",  "LeftCtrl");
        setValue(device, "Start",   "LeftAlt");
    device="Joystick";
    ID="0";
    setValue(device,"Player", player);
    setValue(device,"DeviceNumber",ID);
        setValue(device,"LeftStickAxisX",   "0");
        setValue(device,"LeftStickAxisY",   "1");
        setValue(device,"RightStickAxisX",  "2");
        setValue(device,"RightStickAxisY",  "3");
#elif PLATFORM_WII
    #ifdef PENJIN_SDL_INPUT
        int i = -1;
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"A",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"B",0);
        /*keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"1",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"2",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"+",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"-",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapJoyButton(++i,"HOME",0);*/

        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("UP","UP",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("DOWN","DOWN",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("LEFT","LEFT",0);
        keys.push_back(NULL);
        keys[keys.size()-1] = new KeyMapHat("RIGHT","RIGHT",0);
    #else
        // Use the Wii controls directly.
    #endif
#endif
    // parse through ini file and actually setup the keys
    applyMapping();
    ConfigFile::save(fileName);
}

void KeyMapper::applyMapping()
{
    //  At this point the keymap file should be either loaded or created
    //  And so we read from the loaded ini to actually aply the mapping,

    // Every section refers to a device
    vector<string> devices = getSections();
    for (size_t i = 0; i < devices.size(); ++i)
    {
        CRuint devID = Penjin::StringUtility::stringToInt(getValue(devices.at(i),"DeviceNumber"));
        if(devices.at(i) == "Keyboard")
            mapKey(devID);
        else if(devices.at(i) == "Mouse")
            mapMouse(devID);
        else if(devices.at(i) == "Joystick")
            mapJoy(devID);
    }
}

Penjin::ERRORS KeyMapper::mapKey(CRuchar id)
{
    Penjin::ERRORS result = PENJIN_OK;
    string device = "Keyboard";
    // We will simply get a vector of all the Keys to map
    // then create that mapping
    vector<string> keyList = getKeys(device);
    for(uint i = 0; i < keyList.size(); ++i)
    {
        KeyMapKey* t = NULL;
        t = new KeyMapKey(keyList.at(i), getValue(device,keyList.at(i)), id);
        if(t->isMapValid())
        {
           keys.push_back(t);
        }
        else
        {
            delete t;
            result = PENJIN_ERROR;  // We have to show that something went wrong with the config
        }
    }
    return result;
}

Penjin::ERRORS KeyMapper::mapMouse(CRuchar id)
{
    Penjin::ERRORS result = PENJIN_OK;
    string device = "Mouse";
    vector<string> keyList = getKeys(device);
    for(uint i = 0; i < keyList.size(); ++i)
    {
        KeyMap* t = NULL;
        if(keyList.at(i).find("Button") != keyList.at(i).npos)
        {
            t = new KeyMapMouseButton(Penjin::StringUtility::stringToInt(getValue(device,keyList.at(i))), keyList.at(i), id);
        }
        else
        {
            t = new KeyMapMouseAxis(Penjin::StringUtility::stringToInt(getValue(device,keyList.at(i))), keyList.at(i), id);
        }
        if(t->isMapValid())
        {
           keys.push_back(t);
        }
        else
        {
            delete t;
            result = PENJIN_ERROR;  // We have to show that something went wrong with the config
        }
    }
    return result;
}

Penjin::ERRORS KeyMapper::mapJoy(CRuchar id)
{
    Penjin::ERRORS result = PENJIN_OK;
    string device = "Joystick";
    vector<string> keyList = getKeys(device);
    for(uint i = 0; i < keyList.size(); ++i)
    {
        KeyMap* t = NULL;
        if(keyList.at(i).find("Button") != keyList.at(i).npos)
        {
            t = new KeyMapJoyButton(Penjin::StringUtility::stringToInt(getValue(device,keyList.at(i))), keyList.at(i), id);
        }
        else if(keyList.at(i).find("DigitalAxis") != keyList.at(i).npos)
        {
            int trigger;
            if(keyList.at(i).find("Trigger") != keyList.at(i).npos)
                trigger = Penjin::StringUtility::stringToInt(getValue(device,keyList.at(i)));
            t = new KeyMapDigitalJoyAxis(keyList.at(i), Penjin::StringUtility::stringToInt(getValue(device,keyList.at(i))), trigger,id);
        }
        else if(keyList.at(i).find("Hat") != keyList.at(i).npos)
        {
            t = new KeyMapHat(getValue(device,keyList.at(i)), keyList.at(i), id);
        }
        else if(keyList.at(i).find("Axis") != keyList.at(i).npos)
        {
            t = new KeyMapJoyAxis(Penjin::StringUtility::stringToInt(getValue(device,keyList.at(i))), keyList.at(i), id);
        }
        if(t->isMapValid())
        {
           keys.push_back(t);
        }
        else
        {
            delete t;
            result = PENJIN_ERROR;  // We have to show that something went wrong with the config
        }
    }
    return result;
}

Penjin::ERRORS KeyMapper::mapWii(CRuchar id)
{
    //  TODO Add Wiimapping
    return PENJIN_FUNCTION_IS_STUB;
}

Penjin::ERRORS KeyMapper::mapWiiClassic(CRuchar id)
{
    //  TODO Add Wiimapping
    return PENJIN_FUNCTION_IS_STUB;
}

Penjin::ERRORS KeyMapper::mapWiitar(CRuchar id)
{
    //  TODO Add Wiimapping
    return PENJIN_FUNCTION_IS_STUB;
}
