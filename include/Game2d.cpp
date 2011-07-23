/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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



#include "Game2d.h"
#include "GFX.h"
#include "StringUtility.h"
#include "SimpleJoy.h"
#include "Text.h"
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

    /// TODO: Do something with the error code!

    // Set the title to the main window(localised).
    SDL_WM_SetCaption(title.c_str(), NULL);
}

Penjin::ERRORS Game2d::loadConfig()
{
    Penjin::ConfigFile cfg;
    Penjin::ERRORS e = cfg.load(Penjin::CONFIG_FILE);
    string value;
    Penjin::Renderer* gfx = Penjin::GFX::getInstance();

    value = cfg.getValue("Video","FrameRate","60");
    if(value != "")
    {
        gfx->setFrameRate(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    // NOTE: Value of "0" for Width Height and BitsPerPixel is automatic selection
    value = cfg.getValue("Video","Width","0");
    if(value != "")
    {
        gfx->setWidth(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","Height","0");
    if(value != "")
    {
        gfx->setHeight(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","BaseWidth","0");
    if(value != "")
    {
        gfx->setBaseWidth(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","BaseHeight","0");
    if(value != "")
    {
        gfx->setBaseHeight(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","BitsPerPixel","0");
    if(value != "")
    {
        gfx->setBitsPerPixel(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = cfg.getValue("Video","Fullscreen","False");
    if(value != "")
    {
        gfx->setFullscreen(Penjin::StringUtility::stringToBool(value));
        value = "";
    }
    value = cfg.getValue("Video","ScaleMode","PokeScale");
    if(value != "")
    {
        if(value == "PokeScale")
            gfx->setScaleMode(smPOKESCALE);
        else if(value == "PreScale")
            gfx->setScaleMode(smPRESCALE);
        else
            gfx->setScaleMode(smNONE);
        value = "";
    }
    Penjin::GFX::getInstance()->applyVideoSettings();
    //////////////////////////////////////////////////////////////
    value = cfg.getValue("System","Font","fonts/unispace.ttf");
    if(value != "")
    {
        string font = value;
        value = "";
        value = cfg.getValue("System","FontSize","10");
        if(value != "")
        {
            Penjin::TextMan::getInstance()->load(font,Penjin::StringUtility::stringToInt(value));
        }
        value = "";
    }

    // Save any changes
    if(cfg.hasChanged())
        cfg.save(Penjin::CONFIG_FILE);
    return e;
}

Game2d::~Game2d()
{
    //dtor
}


void Game2d::loop()
{
    //  We have to get the state pointer to begin with
    Penjin::StateManager* sm = Penjin::StateMan::getInstance();
    state = sm->getState();
    while(!state->getShouldQuit())
    {
        //  Then we check states each update loop
        sm->stateManagement();
        state = sm->getState();

        // update joysticks etc
        Penjin::Joy::getInstance()->update();
        state->input();
        //  check for exit condition
        if(Penjin::Joy::getInstance()->isQuit())
        {
            // Break out of loop
            break;
        }


        state->update();    //  Update physics/objects/logic
        state->render();    //  render manually rendered objects
        Penjin::GFX::getInstance()->renderQueue();  //  render objects entrusted into our (to be) optimised render queue
        Penjin::GFX::getInstance()->blit();         //  Force the blit to the screen
        Penjin::GFX::getInstance()->frameLimiter(); //  restrict frame rate
    }
}
