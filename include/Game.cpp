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



#include "Game.h"
#include "GFX.h"
#include "StringUtility.h"
#include "SimpleJoy.h"
#include "Text.h"
#include "ConfigManager.h"

/// If no alternative timer is selected we fallback to using SDL
#ifndef PENJIN_SYS_TIMER
    #define PENJIN_SDL_TIMER
#endif

/// If no alternative Audio engine is selected, we fall back to using SDL
#ifndef PENJIN_AL
    #define PENJIN_SDL_AUDIO
#endif

/// If we are on Pandora AND using GLES we can't use SDL input
#ifdef PLATFORM_PANDORA
    #if defined(PENJIN_ES) || defined(PENJIN_ES2)
        #define PENJIN_SYS_INPUT
    #endif
#endif

/// If no alternative Input handling system is provided use SDL
#ifndef PENJIN_SYS_INPUT
    #define PENJIN_SDL_INPUT
#endif


using Penjin::Game;
using Penjin::ApplicationState;
using Penjin::ConfigManager;

Game::Game()
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

Penjin::ERRORS Game::loadConfig()
{
    ConfigManager* cMan = ConfigMan::getInstance();
    Penjin::ERRORS e = cMan->load();
    if(e != PENJIN_OK)
        return e;

    //  Set the correct renderer based on configurations.
    GPU_SINGLETON::getInstance()->setMode(cMan->getGFXEngine(),cMan->getGFXDimensions());

    //  If the config was accepted by config manager we can apply the settings!
    Penjin::GFX->setFrameRate(cMan->getFrameRate());
    Penjin::GFX->setWidth(cMan->getWidth());
    Penjin::GFX->setHeight(cMan->getHeight());
    Penjin::GFX->setBaseWidth(cMan->getBaseWidth());
    Penjin::GFX->setBaseHeight(cMan->getBaseHeight());
    Penjin::GFX->setBitsPerPixel(cMan->getBPP());
    Penjin::GFX->setFullscreen(cMan->getFullscreen());
    string value = cMan->getScaleMode();
    if(value == "PokeScale")
        Penjin::GFX->setScaleMode(smPOKESCALE);
    else if(value == "PreScale")
        Penjin::GFX->setScaleMode(smPRESCALE);
    else
        Penjin::GFX->setScaleMode(smNONE);

    Penjin::GFX->applyVideoSettings();
    Penjin::TextMan::getInstance()->load(cMan->getSystemFont(), cMan->getSystemFontSize());
    return e;
}

Game::~Game()
{
    //dtor
    ConfigMan::getInstance()->save();
}


void Game::loop()
{
    //  We have to get the state pointer to begin with
    Penjin::StateManager* sm = Penjin::StateMan::getInstance();
    Penjin::Renderer* gfx = Penjin::GFX;
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
        state->update();        //  Update physics/objects/logic
        state->render();        //  render manually rendered objects
        gfx->renderQueue();     //  render objects entrusted into our (to be) optimised render queue
        gfx->blit();            //  Force the blit to the screen
        gfx->frameLimiter();    //  restrict frame rate
    }
}
