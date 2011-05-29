/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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



#include "Game2d.h"
#include "StateTitle.h"
#include "GFX.h"
#include "StringUtility.h"
#include "SimpleJoy.h"
using Penjin::Game2d;
using Penjin::ApplicationState;

Game2d::Game2d()
{
    //ctor
    Penjin::ERRORS e = PENJIN_OK;
    Uint32 flags=0;
    #if defined (PENJIN_SDL_VIDEO) || defined(PENJIN_SDL)
        flags = flags | SDL_INIT_VIDEO;
    #endif
    #if defined (PENJIN_SDL_AUDIO) || defined(PENJIN_SDL)
        //  Set SDL_Mixer
        flags = flags | SDL_INIT_AUDIO;
    #endif
    #if defined (PENJIN_SDL_INPUT) || defined(PENJIN_SDL)
        //  Setup SDL input handling
        flags = flags | SDL_INIT_JOYSTICK;
    #endif
    #if defined (PENJIN_SDL_TIMER) || defined(PENJIN_SDL)
        //  Setup SDL timer
        flags = flags | SDL_INIT_TIMER;
    #endif
    if(flags != 0)
    {
        //  TODO handle error properly
        if(SDL_Init(flags) < 0)
            e = PENJIN_SDL_SOMETHING_FAILED;
    }

    //  Load video config
    if(e == PENJIN_OK)
        e = loadConfig();
    //  If there is a problem with loading the cfg, create a default config
    if(e != PENJIN_OK)
        defaultConfig();
    if(flags)
        Penjin::GFX::getInstance()->applyVideoSettings();
}

Penjin::ERRORS Game2d::loadConfig()
{
    Penjin::ConfigFile cfg;
    Penjin::ERRORS e = cfg.load(Penjin::CONFIG_FILE);
    string value;
    /// TODO: errors for missing config elements

    value = cfg.getValue("Video","FrameRate");
    if(value != "")
    {
        Penjin::GFX::getInstance()->setFrameRate(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","Width");
    if(value != "")
    {
        Penjin::GFX::getInstance()->setWidth(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","Height");
    if(value != "")
    {
        Penjin::GFX::getInstance()->setHeight(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","BitsPerPixel");
    if(value != "")
    {
        Penjin::GFX::getInstance()->setBitsPerPixel(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","Fullscreen");
    if(value != "")
    {
        Penjin::GFX::getInstance()->setFullscreen(Penjin::StringUtility::stringToBool(value));
        value = "";
    }
    return e;
}

void Game2d::defaultConfig()
{
    Penjin::ConfigFile cfg;

    string section = "Video";
    cfg.setValue(section, "FrameRate", "60");
    //  Setting Width and Height to 0 is auto resolution.
    cfg.setValue(section, "Width","0");
    cfg.setValue(section, "Height","0");
    //  0 is Auto BPP
    cfg.setValue(section,"BitsPerPixel", "0");
    cfg.setValue(section,"Fullscreen","false");

    section = "Locale";
    cfg.setValue(section, "LanguageFolder", "strings");
    cfg.setValue(section, "Language","en_GB");
    cfg.save(Penjin::CONFIG_FILE);
}

Game2d::~Game2d()
{
    //dtor
}


void Game2d::loop()
{
    //  We have to get the state pointer to begin with
    state = Penjin::StateMan::getInstance()->getState();
    while(!state->getShouldQuit())
    {
        //  Then we check states each update loop
        Penjin::StateMan::getInstance()->stateManagement();
        state = Penjin::StateMan::getInstance()->getState();

        // update joysticks etc
        Penjin::Joy::getInstance()->update();
        state->input();
        //  check for exit condition
        if(Penjin::Joy::getInstance()->isQuit())
        {
            // Break out of loop
            break;
        }

        state->update();
        state->render();
        Penjin::GFX::getInstance()->renderQueue();
        Penjin::GFX::getInstance()->blit();
        Penjin::GFX::getInstance()->frameLimiter();
    }
}
