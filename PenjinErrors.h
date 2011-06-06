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
#pragma once
#ifndef PENJINERRORS_H
#define PENJINERRORS_H

#include <string>
using namespace std;
//	List all error codes here
namespace PenjinErrors
{
    enum PENJIN_ERRORS
    {
        //  General Errors
        PENJIN_ERROR = -1,
        PENJIN_OK,
        PENJIN_PARSE_ERROR,
        PENJIN_FILE_NOT_FOUND,
        PENJIN_UNABLE_TO_SAVE,
        PENJIN_TEXTURE_CONVERSION_ERROR,
        PENJIN_NO_COMMANDLINE,
        PENJIN_INVALID_COMMANDLINE,
        PENJIN_INVALID_INDEX,
        PENJIN_INVALID_MENUITEM_TYPE,
        PENJIN_UNDEFINED_STATE,
        PENJIN_FUNCTION_IS_STUB,

        //  SDL_image
        PENJIN_IMG_UNABLE_TO_OPEN,
        //  SDL_ttf
        PENJIN_TTF_UNABLE_TO_OPEN,
        //  SDL misc stuff
        PENJIN_SDL_SOMETHING_FAILED,
        PENJIN_SDL_VIDEO_INIT_FAILED,
        PENJIN_SDL_VIDEO_QUERY_FAILED,
        PENJIN_SDL_SETVIDEOMODE_FAILED,
        PENJIN_SDL_INVALID_COLORKEY,
        PENJIN_SDL_HAS_ALPHA_CHANNEL,
        //  EGL
        PENJIN_EGL_NO_DISPLAY,
        PENJIN_EGL_INIT_FAILED,
        PENJIN_EGL_NO_CONTEXT,

        //  devkitpro libFAT
        PENJIN_FAT_INIT_FAILED,
        PENJIN_FAT_GET_ROOT_FAILED,
        PENJIN_FAT_ACCESS_ROOT_FAILED,
        //  Penjin status
        PENJIN_SHUTDOWN,
        PENJIN_GOODBYE
    };
#ifndef GUARD_PENJIN_ERROR_STRINGS
#define GUARD_PENJIN_ERROR_STRINGS
    #ifdef PLATFORM_WII
    static char* PENJIN_ERROR_STRINGS[] =
    #else
    static string PENJIN_ERROR_STRINGS[] =
    #endif
    {
        "An error occurred.",
        "No errors detected.",
        "Parser Error. Check script.",
        "File not found.",
        "Unable to save file.",
        "Texture conversion error.",
        "No command line args provided.",
        "Invalid command line.",
        "Array out of bounds. Invalid index.",
        "MenuItem type is invalid.",
        "The State was undefined. check stateManagement().",
        "The function is a stub and incomplete.",

        "Unable to open file.",

        "Unable to open file.",

        "SDL failed to initialise.",
        "SDL video initialisation failed.",
        "SDL video query failed.",
        "SDL_SetVideoMode failed.",
        "SDL_SetColorKey failed.",
        "SDL_SetColorKey failed - Image has full alpha channel.",
        //  EGL
        "eglGetDisplay failed. Unable to access local windowing system.",
        "eglInitialize failed.",
        "eglCreateContext failed.",

        "FATlib Initialisation Error.",
        "FATlib Get root filesystem failed.",
        "FATlib Change Directory to root failed.",

        "Shutting Down.",
        "Goodbye! ^_^"
    };
#endif //GUARD_PENJIN_ERROR_STRINGS
}
#endif	//	PENJINERRORS_H
