/**
	\section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012
	Kevin Winfield-Pantoja

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
/***************************************************************************************************
*   \file ConfigManager is where PenjinTwo stores all settings.
*   \author Kevin Winfield-Pantoja
*/

#include "ConfigManager.h"
#include "IniFile.h"
#include "ErrorHandler.h"
#include "StringUtility.h"

using Penjin::ConfigManager;
using Penjin::IniFile;
using Penjin::ErrorHandler;

ConfigManager::ConfigManager() : config(NULL)
{
    //ctor
    config = new IniFile;
}

ConfigManager::~ConfigManager()
{
    //dtor
    delete config;
}

Penjin::ERRORS ConfigManager::load(const string& fn)
{
    /// This loading function is to be called AFTER various components have reported their features to ConfigManager.

    // First we load the raw config file
    Penjin::ERRORS e = PENJIN_ERROR;
    if (fn == "")
        e = config->load(Penjin::CONFIG_FILE);
    else
        e = config->load(fn);

    // If the file is not found we can create it!
    // But we return for any other errors!
    if(e != PENJIN_OK && e != PENJIN_FILE_NOT_FOUND)
        return e;
    e = PENJIN_OK;
    // Check for renderers and audio Engines
    //  Check for SDL or GL output
    string value = config->getValue("Video","Engine","SDL");
    if(value != "")
    {
        if(value == "SDL" && checkReport("GFXSDL"))
            setGFXEngine("SDL");
        else if(value == "GL" && checkReport("GFXGL"))
            setGFXEngine("GL");
        value = "";
    }
    //  Check if we require the Z dimension or not.
    value = config->getValue("Video","Dimensions","2");
    if(value != "")
    {
        if(value == "2" && checkReport("GFX2D"))
            setGFXDimensions(2);
        else if(value == "3" && checkReport("GFX3D"))
            setGFXDimensions(3);
        value = "";
    }
    //  Check the Audio Engine used
    value = config->getValue("Audio","Engine","SDL");
    if(value != "")
    {
        if(value == "SDL" && checkReport("AudioSDL"))
            setAudioEngine("SDL");
        else if(value == "AL" && checkReport("AudioAL"))
            setAudioEngine("AL");
        value = "";
    }
    value = config->getValue("Video","FrameRate","60");
    if(value != "")
    {
        this->setFrameRate(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = config->getValue("Physics","UpdateRate","60");
    if(value != "")
    {
        this->setUpdateRate(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    // NOTE: Value of "0" for Width Height and BitsPerPixel is automatic selection
    value = config->getValue("Video","Width","0");
    if(value != "")
    {
        setWidth(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = config->getValue("Video","Height","0");
    if(value != "")
    {
        setHeight(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = config->getValue("Video","BaseWidth","0");
    if(value != "")
    {
        setBaseWidth(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = config->getValue("Video","BaseHeight","0");
    if(value != "")
    {
        setBaseHeight(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = config->getValue("Video","BitsPerPixel","0");
    if(value != "")
    {
        setBPP(Penjin::StringUtility::stringToInt(value));
        value = "";
    }
    value = config->getValue("Video","Fullscreen","False");
    if(value != "")
    {
        setFullscreen(Penjin::StringUtility::stringToBool(value));
        value = "";
    }
    value = config->getValue("Video","ScaleMode","PokeScale");
    if(value != "")
    {
        if(value == "PokeScale" || value == "PreScale")
            setScaleMode(value);
        else
            setScaleMode("None");
        value = "";
    }
    //////////////////////////////////////////////////////////////
    value = config->getValue("System","Font","fonts/unispace.ttf");
    if(value != "")
    {
        string font = value;
        value = "";
        value = config->getValue("System","FontSize","10");
        if(value != "")
        {
            setSystemFont(font);
            setSystemFontSize(Penjin::StringUtility::stringToInt(value));
        }
        value = "";
    }
    return e;
}

Penjin::ERRORS ConfigManager::save(const string& fn)
{
    Penjin::ERRORS e = PENJIN_ERROR;
    if (fn == "")
        e = config->save(Penjin::CONFIG_FILE);
    else
        e = config->save(fn);
    return e;
}

bool ConfigManager::report(const string& feature)
{
    //  We check if the feature is a valid feature and we also check if it has already been reported or not...
    if((feature == "AudioSDL" || feature == "AudioAL" || feature == "GFXSDL" || feature == "GFXGL" || feature == "GFX2D" || feature == "GFX3D")
       && !checkReport(feature))
        reportList+=feature;
    else
        return false;

    return true;
}

bool ConfigManager::checkReport(const string& feature)
{
    if(reportList.find(feature) != string::npos)
    {
        ErrorMan::getInstance()->print("ConfigManager is unable to use feature " + feature + "! and safe defaults will be used.");
        return false;
    }
    return true;
}


//  set which library handles audio.
void ConfigManager::setAudioEngine(const string& engine)
{
    engineAudio = engine;
}

//  Set which library handles display.
void ConfigManager::setGFXEngine(const string& engine)
{
    engineGFX = engine;
}

//  Set whether to handle the third dimensions (depth)
void ConfigManager::setGFXDimensions(const uint& dims)
{
    dimensions = dims;
}

//  Set the FrameRate
void ConfigManager::setFrameRate(const int& fps)
{
    this->fps = fps;
}

//  Set the physics update rate
void ConfigManager::setUpdateRate(const int& fps)
{
    updateps = fps;
}

//  Set the Display Width (0 == autodetect)
void ConfigManager::setWidth(const int& w)
{
    width = w;
}

//  Set the display height (0 == Autodetect)
void ConfigManager::setHeight(const int& h)
{
    height = h;
}

//  Set the Unscaled Display Width (0 == autodetect)
void ConfigManager::setBaseWidth(const int& w)
{
    baseWidth = w;
}

//  Set the Unscaled display height (0 == Autodetect)
void ConfigManager::setBaseHeight(const int& h)
{
    baseHeight = h;
}

//  Set the BitsPerPixel of the display (0 == Auto)
void ConfigManager::setBPP(const int& bpp)
{
    this->bpp = bpp;
}

//  Set if the application is fullscreen or not (true == fullscreen)
void ConfigManager::setFullscreen(const bool& fs)
{
    fullscreen = fs;
}

//  Set the ScaleMode of the application (None,PreScale,PokeScale)
void ConfigManager::setScaleMode(const string& sm)
{
    scaleMode = sm;
}

//  Set the default SystemFont
void ConfigManager::setSystemFont(const string& sf)
{
    font = sf;
}

void ConfigManager::setSystemFontSize(const int& fs)
{
    fontSize = fs;
}


//  Get which library handles audio.
string ConfigManager::getAudioEngine()
{
    return engineAudio;
}

//  Get which library handles display.
string ConfigManager::getGFXEngine()
{
    return engineGFX;
}

//  Get whether to handle the third dimensions (depth)
uint ConfigManager::getGFXDimensions()
{
    return dimensions;
}

//  Get the FrameRate
int ConfigManager::getFrameRate()
{
    return fps;
}

//  Get the physics update rate
int ConfigManager::getUpdateRate()
{
    return updateps;
}

//  Get the Display Width (0 == autodetect)
int ConfigManager::getWidth()
{
    return width;
}

//  Get the display height (0 == Autodetect)
int ConfigManager::getHeight()
{
    return height;
}

//  Get the Unscaled Display Width (0 == autodetect)
int ConfigManager::getBaseWidth()
{
    return baseWidth;
}

//  Get the Unscaled display height (0 == Autodetect)
int ConfigManager::getBaseHeight()
{
    return baseHeight;
}

//  Get the BitsPerPixel of the display (0 == Auto)
int ConfigManager::getBPP()
{
    return bpp;
}

//  Get if the application is fullscreen or not (true == fullscreen)
bool ConfigManager::getFullscreen()
{
    return fullscreen;
}

//  Get the ScaleMode of the application (None,PreScale,PokeScale)
string ConfigManager::getScaleMode()
{
    return scaleMode;
}

//  Get the default SystemFont
string ConfigManager::getSystemFont()
{
    return font;
}

int ConfigManager::getSystemFontSize()
{
    return fontSize;
}

