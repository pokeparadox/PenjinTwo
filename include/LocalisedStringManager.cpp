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
#include "LocalisedStringManager.h"
using Penjin::LocalisedStringManager;

//LocalisedStringManager* LocalisedStringManager::instance=NULL;

LocalisedStringManager::LocalisedStringManager() : languageFolder("strings"), language("eng_GB")
{
    //ctor
}

LocalisedStringManager::~LocalisedStringManager()
{
    //dtor
    if(hasChanged())
        save();
}

/*LocalisedStringManager* LocalisedStringManager::getInstance()
{
    if( instance == NULL )
    {
        instance = new LocalisedStringManager;
    }
    return instance;
}*/

void LocalisedStringManager::setLanguage(const string& l)
{
    language = l;
}

void LocalisedStringManager::setLanguageFolder(const string& f)
{
    languageFolder = f;
}

Penjin::ERRORS LocalisedStringManager::load()
{
    fileName = "./"+languageFolder+"/"+language+".lng";
    return this->IniFile::load(fileName);
}

Penjin::ERRORS LocalisedStringManager::save()
{
    fileName = "./"+languageFolder+"/"+language+".lng";
    return this->IniFile::save(fileName);
}

