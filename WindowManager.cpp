/**
    \section LICENSE
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
**********************************************************************************************/
/**
  * \file WindowManager is a simple WindowManager to handle several instances of Window
  * \author Kevin Winfield-Pantoja
*/
#include "WindowManager.h"
#include "Window.h"
using Penjin::WindowManager;
using Penjin::Window;
WindowManager::WindowManager()
{
    //ctor
}

WindowManager::~WindowManager()
{
    //dtor
    clear();
}

void WindowManager::render()
{
    //  The Windows themselves determine if to render or not.
    for(int i = windows.size()-1; i >=0; --i)
        windows.at(i)->render();
}

void WindowManager::update()
{
    for(int i = windows.size()-1; i >=0; --i)
        windows.at(i)->update();
    // Work out which windows will be visible or not
}

void WindowManager::add(Window* w)
{
    windows.push_back(w);
}

void WindowManager::minimise()
{
    for(int i = windows.size()-1; i >=0; --i)
        windows.at(i)->minimise();
}

void WindowManager::clear()
{
    windows.clear();
}
