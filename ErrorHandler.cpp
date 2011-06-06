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
#include "ErrorHandler.h"
#include "Errors.h"
#include "LocalisedStringManager.h"
using Penjin::ErrorHandler;
using Penjin::ERRORS;
using Penjin::LocaleMan;


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
}

ErrorHandler::~ErrorHandler()
{

}

string ErrorHandler::getErrorText(const string& error)
{
    return Penjin::LocaleMan::getInstance()->getValue("Errors",error);
}

string ErrorHandler::getErrorText(const ERRORS& error)
{
    //return getErrorText(stringToEnum(error));
    return "PENJIN_FUNCTION_IS_STUB";
}
