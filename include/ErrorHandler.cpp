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
#include "ErrorHandler.h"
#include "Errors.h"
#include "LocalisedStringManager.h"
#include <iostream>
#include <cstdlib>
using namespace std;
using Penjin::ErrorHandler;
using Penjin::ERRORS;
using Penjin::LocaleMan;


//ErrorHandler* ErrorHandler::instance = NULL;

ErrorHandler::ErrorHandler()
{
        //  General Errors
        enumMap["PENJIN_ERROR"] = PENJIN_ERROR;
        enumMap["PENJIN_OK"] = PENJIN_OK;
        enumMap["PENJIN_PARSE_ERROR"] = PENJIN_PARSE_ERROR;
        enumMap["PENJIN_FILE_NOT_FOUND"] = PENJIN_FILE_NOT_FOUND;
        enumMap["PENJIN_UNABLE_TO_SAVE"] = PENJIN_UNABLE_TO_SAVE;
        enumMap["PENJIN_TEXTURE_CONVERSION_ERROR"] = PENJIN_TEXTURE_CONVERSION_ERROR;
        enumMap["PENJIN_NO_COMMANDLINE"] = PENJIN_NO_COMMANDLINE;
        enumMap["PENJIN_INVALID_COMMANDLINE"] = PENJIN_INVALID_COMMANDLINE;
        enumMap["PENJIN_INVALID_INDEX"] = PENJIN_INVALID_INDEX;
        enumMap["PENJIN_INVALID_MENUITEM_TYPE"] = PENJIN_INVALID_MENUITEM_TYPE;
        enumMap["PENJIN_UNDEFINED_STATE"] = PENJIN_UNDEFINED_STATE;
        enumMap["PENJIN_FUNCTION_IS_STUB"] = PENJIN_FUNCTION_IS_STUB;

        //  SDL_image
        enumMap["PENJIN_IMG_UNABLE_TO_OPEN"] = PENJIN_IMG_UNABLE_TO_OPEN;
        //  SDL_ttf
        enumMap["PENJIN_TTF_UNABLE_TO_OPEN"] = PENJIN_TTF_UNABLE_TO_OPEN;
        //  SDL misc stuff
        enumMap["PENJIN_SDL_SOMETHING_FAILED"] = PENJIN_SDL_SOMETHING_FAILED;
        enumMap["PENJIN_SDL_VIDEO_INIT_FAILED"] = PENJIN_SDL_VIDEO_INIT_FAILED;
        enumMap["PENJIN_SDL_VIDEO_QUERY_FAILED"] = PENJIN_SDL_VIDEO_QUERY_FAILED;
        enumMap["PENJIN_SDL_SETVIDEOMODE_FAILED"] = PENJIN_SDL_SETVIDEOMODE_FAILED;
        enumMap["PENJIN_SDL_INVALID_COLORKEY"] = PENJIN_SDL_INVALID_COLORKEY;
        enumMap["PENJIN_SDL_HAS_ALPHA_CHANNEL"] = PENJIN_SDL_HAS_ALPHA_CHANNEL;
        //  EGL
        enumMap["PENJIN_EGL_NO_DISPLAY"] = PENJIN_EGL_NO_DISPLAY;
        enumMap["PENJIN_EGL_INIT_FAILED"] = PENJIN_EGL_INIT_FAILED;
        enumMap["PENJIN_EGL_NO_CONTEXT"] = PENJIN_EGL_NO_CONTEXT;

        //  devkitpro libFAT
        enumMap["PENJIN_FAT_INIT_FAILED"] = PENJIN_FAT_INIT_FAILED;
        enumMap["PENJIN_FAT_GET_ROOT_FAILED"] = PENJIN_FAT_GET_ROOT_FAILED;
        enumMap["PENJIN_FAT_ACCESS_ROOT_FAILED"] = PENJIN_FAT_ACCESS_ROOT_FAILED;
        //  Penjin status
        enumMap["PENJIN_SHUTDOWN"] = PENJIN_SHUTDOWN;
        enumMap["PENJIN_GOODBYE"] = PENJIN_GOODBYE;

        //////////////////
        //  General Errors in string format from grabbing localised versions from locale file
        valMap[PENJIN_ERROR] = "PENJIN_ERROR";
        valMap[PENJIN_OK] = "PENJIN_OK";
        valMap[PENJIN_PARSE_ERROR] = "PENJIN_PARSE_ERROR";
        valMap[PENJIN_FILE_NOT_FOUND] = "PENJIN_FILE_NOT_FOUND";
        valMap[PENJIN_UNABLE_TO_SAVE] = "PENJIN_UNABLE_TO_SAVE";
        valMap[PENJIN_TEXTURE_CONVERSION_ERROR] = "PENJIN_TEXTURE_CONVERSION_ERROR";
        valMap[PENJIN_NO_COMMANDLINE] = "PENJIN_NO_COMMANDLINE";
        valMap[PENJIN_INVALID_COMMANDLINE] = "PENJIN_INVALID_COMMANDLINE";
        valMap[PENJIN_INVALID_INDEX] = "PENJIN_INVALID_INDEX";
        valMap[PENJIN_INVALID_MENUITEM_TYPE] = "PENJIN_INVALID_MENUITEM_TYPE";
        valMap[PENJIN_UNDEFINED_STATE] = "PENJIN_UNDEFINED_STATE";
        valMap[PENJIN_FUNCTION_IS_STUB] = "PENJIN_FUNCTION_IS_STUB";

        //  SDL_image
        valMap[PENJIN_IMG_UNABLE_TO_OPEN] = "PENJIN_IMG_UNABLE_TO_OPEN";
        //  SDL_ttf
        valMap[PENJIN_TTF_UNABLE_TO_OPEN] = "PENJIN_TTF_UNABLE_TO_OPEN";
        //  SDL misc stuff
        valMap[PENJIN_SDL_SOMETHING_FAILED] = "PENJIN_SDL_SOMETHING_FAILED";
        valMap[PENJIN_SDL_VIDEO_INIT_FAILED] = "PENJIN_SDL_VIDEO_INIT_FAILED";
        valMap[PENJIN_SDL_VIDEO_QUERY_FAILED] = "PENJIN_SDL_VIDEO_QUERY_FAILED";
        valMap[PENJIN_SDL_SETVIDEOMODE_FAILED] = "PENJIN_SDL_SETVIDEOMODE_FAILED";
        valMap[PENJIN_SDL_INVALID_COLORKEY] = "PENJIN_SDL_INVALID_COLORKEY";
        valMap[PENJIN_SDL_HAS_ALPHA_CHANNEL] = "PENJIN_SDL_HAS_ALPHA_CHANNEL";
        //  EGL
        valMap[PENJIN_EGL_NO_DISPLAY] = "PENJIN_EGL_NO_DISPLAY";
        valMap[PENJIN_EGL_INIT_FAILED] = "PENJIN_EGL_INIT_FAILED";
        valMap[PENJIN_EGL_NO_CONTEXT] = "PENJIN_EGL_NO_CONTEXT";

        //  devkitpro libFAT
        valMap[PENJIN_FAT_INIT_FAILED] = "PENJIN_FAT_INIT_FAILED";
        valMap[PENJIN_FAT_GET_ROOT_FAILED] = "PENJIN_FAT_GET_ROOT_FAILED";
        valMap[PENJIN_FAT_ACCESS_ROOT_FAILED] = "PENJIN_FAT_ACCESS_ROOT_FAILED";
        //  Penjin status
        valMap[PENJIN_SHUTDOWN] = "PENJIN_SHUTDOWN";
        valMap[PENJIN_GOODBYE] = "PENJIN_GOODBYE";

        //  This is the default unlocalised errortext
        defText[PENJIN_ERROR] = "An error occurred.";
        defText[PENJIN_OK] = "No errors detected.";
        defText[PENJIN_PARSE_ERROR] = "Parser Error. Check script.";
        defText[PENJIN_FILE_NOT_FOUND] = "File not found.";
        defText[PENJIN_UNABLE_TO_SAVE] = "Unable to save file.";
        defText[PENJIN_TEXTURE_CONVERSION_ERROR] = "Texture conversion error.";
        defText[PENJIN_NO_COMMANDLINE] = "No command line args provided.";
        defText[PENJIN_INVALID_COMMANDLINE] = "Invalid command line.";
        defText[PENJIN_INVALID_INDEX] = "Array out of bounds. Invalid index.";
        defText[PENJIN_INVALID_MENUITEM_TYPE] = "MenuItem type is invalid.";
        defText[PENJIN_UNDEFINED_STATE] = "The State was undefined. check stateManagement().";
        defText[PENJIN_FUNCTION_IS_STUB] = "The function is a stub and incomplete.";

        //  SDL_image
        defText[PENJIN_IMG_UNABLE_TO_OPEN] = "Unable to open Image file.";
        //  SDL_ttf
        defText[PENJIN_TTF_UNABLE_TO_OPEN] = "Unable to open TTF file.";
        //  SDL misc stuff
        defText[PENJIN_SDL_SOMETHING_FAILED] = "SDL failed to initialise.";
        defText[PENJIN_SDL_VIDEO_INIT_FAILED] = "Failed to initialise the SDL Video sub-system.";
        defText[PENJIN_SDL_VIDEO_QUERY_FAILED] = "SDL video query failed.";
        defText[PENJIN_SDL_SETVIDEOMODE_FAILED] = "SDL_SetVideoMode failed.";
        defText[PENJIN_SDL_INVALID_COLORKEY] = "SDL_SetColorKey failed.";
        defText[PENJIN_SDL_HAS_ALPHA_CHANNEL] = "SDL_SetColorKey failed - Image has full alpha channel.";
        //  EGL
        defText[PENJIN_EGL_NO_DISPLAY] = "eglGetDisplay failed. Unable to access local windowing system.";
        defText[PENJIN_EGL_INIT_FAILED] ="eglInitialize failed.";
        defText[PENJIN_EGL_NO_CONTEXT] = "eglCreateContext failed.";

        //  devkitpro libFAT
        defText[PENJIN_FAT_INIT_FAILED] =  "FATlib Initialisation Error.";
        defText[PENJIN_FAT_GET_ROOT_FAILED] = "FATlib Get root filesystem failed.";
        defText[PENJIN_FAT_ACCESS_ROOT_FAILED] = "FATlib Change Directory to root failed.";
        //  Penjin status
        defText[PENJIN_SHUTDOWN] = "Shutting Down.";
        defText[PENJIN_GOODBYE] = "Goodbye! ^_^";
}

ErrorHandler::~ErrorHandler()
{

}


/*ErrorHandler* ErrorHandler::getInstance()
{
    if( instance == NULL )
    {
        instance = new ErrorHandler;
    }
    return instance;
}*/

string ErrorHandler::getErrorText(const string& error)
{
    return Penjin::LocaleMan::getInstance()->getValue("Errors",error,getDefaultText(error));
}

string ErrorHandler::getErrorText(const ERRORS& error)
{
    return Penjin::LocaleMan::getInstance()->getValue("Errors", enumToString(error),getDefaultText(error));
}

string ErrorHandler::getDefaultText(const string& error)
{
    return getDefaultText(stringToEnum(error));
}

string ErrorHandler::getDefaultText(const ERRORS& error)
{
    return defText.find(error)->second;
}

void ErrorHandler::print(const ERRORS& error, const string& info)
{
    cout << "Penjin Says: ";
    if(info == "")
        cout << getErrorText(error) << endl;
    else
        cout << getErrorText(error) << " - " << info << endl;
}

void ErrorHandler::print(const string& msg)
{
    cout << "INFO: " << msg << endl;
}

void ErrorHandler::forceQuit(const ERRORS& error, const string& info)
{
    print(error,info);
    exit(error);
}
