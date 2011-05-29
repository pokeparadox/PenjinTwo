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
#include <string>
#include <iostream>
#include "Application.h"
using Penjin::Application;
using std::string;
using std::cout;
using std::endl;

Application::Application() : state(NULL)
{
    //ctor
    //  We load the settings file for the app
    Penjin::ConfigFile conf;
    ERRORS error = conf.load(Penjin::CONFIG_FILE);

    //  If settings.ini not found create a default
    if(error == PENJIN_FILE_NOT_FOUND)
        createDefaultSettings();

    // Find out the current language
    Penjin::LocaleMan::getInstance()->setLanguageFolder(conf.getValue("Locale","LanguageFolder"));
    Penjin::LocaleMan::getInstance()->setLanguage(conf.getValue("Locale","Language"));
    error = Penjin::LocaleMan::getInstance()->load();
    if(error == PENJIN_FILE_NOT_FOUND)
    {
        // If locale not found we can only give English error.
        cout << "Error loading Locale file!" << endl;
    }
    //  Set localised title
    this->setTitle( (string)Penjin::LocaleMan::getInstance()->getValue("Application","Title") );
}

Application::~Application()
{
    //dtor
    StateMan::getInstance()->clearState();
}


void Application::createDefaultSettings()
{

}

Penjin::ERRORS Application::argHandler(int argc, char** argv)
{
    return PENJIN_FUNCTION_IS_STUB;
}

void Application::quit()
{

}
