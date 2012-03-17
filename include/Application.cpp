/*
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

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
#include <string>
#include <iostream>
#include "Application.h"
#include "ErrorHandler.h"
#include "ConfigManager.h"
using Penjin::Application;
using std::string;
using std::cout;
using std::endl;

Application::Application() : state(NULL)
{
    //ctor
    //  We load the settings file for the app
    Penjin::IniFile conf;
    ERRORS error = conf.load(Penjin::CONFIG_FILE);

    // Find out the current language
    Penjin::LocaleMan::getInstance()->setLanguageFolder(conf.getValue("Locale","LanguageFolder","strings"));
    Penjin::LocaleMan::getInstance()->setLanguage(conf.getValue("Locale","Language","en_GB"));
    error = Penjin::LocaleMan::getInstance()->load();
    if(error == PENJIN_FILE_NOT_FOUND)
    {
        // If locale not found we can only give English error.
        ErrorMan::getInstance()->print(error,"Locale not found, creating default.");
    }
    //  Set localised title
    this->setTitle( (string)Penjin::LocaleMan::getInstance()->getValue("Application","Title","PenjinTwo Application") );
    // We save any changes to the config
    if(conf.hasChanged())
        conf.save(Penjin::CONFIG_FILE);
    if(Penjin::LocaleMan::getInstance()->hasChanged())
        Penjin::LocaleMan::getInstance()->save();
}

Application::~Application()
{
    //dtor
    StateMan::getInstance()->clear();
    // We save any changes to the config

    if(Penjin::LocaleMan::getInstance()->hasChanged())
        Penjin::LocaleMan::getInstance()->save();
}


void Application::createDefaultSettings()
{

}

Penjin::ERRORS Application::argHandler(int argc, char** argv)
{
    ErrorMan::getInstance()->print(PENJIN_FUNCTION_IS_STUB);
    return PENJIN_FUNCTION_IS_STUB;
}

void Application::quit()
{

}
