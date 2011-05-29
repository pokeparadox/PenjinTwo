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
#include "Penjin.h"

namespace Penjin
{
    string appName = "Penjin";
    #ifdef PLATFORM_WII
        string workingDir = "sd/" + appName +"/";
    #endif
}

PenjinErrors::PENJIN_ERRORS Penjin::canOpenRoot()
{
    #ifdef PLATFORM_WII
        DIR_ITER *root = diropen("sd/");
    #elif _WIN32
        DIR *root = opendir("C:\\");
    #else // _LINUX
        DIR *root = opendir("/");
    #endif
    if (root)
    {
        #ifdef PLATFORM_WII
            dirclose(root);
        #elif _WIN32
            closedir(root);
        #else // _LINUX
            closedir(root);
        #endif

       return PenjinErrors::PENJIN_OK;
    }
    return PenjinErrors::PENJIN_FAT_GET_ROOT_FAILED;
}

#ifdef PLATFORM_WII
PenjinErrors::PENJIN_ERRORS Penjin::initFileSystem()
{
    PenjinErrors::PENJIN_ERRORS e;
    if (!fatInitDefault())
        return PenjinErrors::PENJIN_FAT_INIT_FAILED;
    e = canOpenRoot();
    if (e!= PenjinErrors::PENJIN_OK)
        return e;
    /*if (chdir("sd/"))
        return PenjinErrors::PENJIN_FAT_ACCESS_ROOT_FAILED;*/
    return PenjinErrors::PENJIN_OK;
}

void Penjin::setWorkingDirectory(CRstring dir)
{
    workingDir = dir;
}

string Penjin::getWorkingDirectory()
{
    return workingDir;
}

void Penjin::deInitFileSystem()
{
    fatUnmount(0);                  //  Unmount the FAT system from whatever stage it may be.
}
#endif


void Penjin::setApplicationName(CRstring n)
{
    appName = n;
}

string Penjin::getApplicationName()
{
    return appName;
}

