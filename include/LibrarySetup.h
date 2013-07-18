#ifndef LIBRARYSETUP_H_INCLUDED
#define LIBRARYSETUP_H_INCLUDED

/**
    \section LICENSE
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
**********************************************************************************************/
/**
  * \file LibrarySetup is a file to export correctly when building for Windows.
  * \author Kevin Winfield-Pantoja
*/

#if defined(_WIN32) || defined(__WIN32__)
  #if defined(PENJIN_BUILD_DLL) // We are building the library
    #define  LIB_EXPORT __declspec(dllexport)
  #else
    #define  LIB_EXPORT __declspec(dllimport)
  #endif /* PENJIN_BUILD_DLL */
#else
 #define LIB_EXPORT
#endif

#endif // LIBRARYSETUP_H_INCLUDED
