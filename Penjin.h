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
#ifndef PENJIN_H
#define PENJIN_H

/* The Penjin System Object
Handles setup and keeps track of useful global variables.
Also provides some quick init functions
*/

#include "ErrorHandler.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef PLATFORM_WII
    #include <fat.h>
#else

#endif

namespace Penjin
{
    void setApplicationName(CRstring name);                     //  set the application name
    string getApplicationName();                                //  get the app name.
    PenjinErrors::PENJIN_ERRORS canOpenRoot();              //  tries to get the root directory of the FS
    #ifdef PLATFORM_WII
        PenjinErrors::PENJIN_ERRORS initFileSystem();           //  initialises SD card access.
        void deInitFileSystem();
        void setWorkingDirectory(CRstring dir);                 //  Set the dir that this program runs in
        string getWorkingDirectory();                           //  Get the program dir.
    #endif
}

#endif // PENJIN_H
