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

#include "ConfigFile.h"

#include <string>
using Penjin::ConfigFile;
using std::string;

ConfigFile::ConfigFile() : ini(NULL), changed(false)
{
    //ctor
    ini = new CSimpleIniA;
}

ConfigFile::~ConfigFile()
{
    //dtor
    delete ini;
}

Penjin::ERRORS ConfigFile::load(const string& fileName)
{
    return getError(ini->LoadFile(fileName.c_str()));
}

Penjin::ERRORS ConfigFile::save(const string& fileName)
{
    changed = false;
    return getError(ini->SaveFile(fileName.c_str()));
}

string ConfigFile::getValue(const string& section, const string& key)
{
    if(ini->GetValue(section.c_str(),key.c_str(),NULL) == NULL)
        return "";
    return (string)ini->GetValue(section.c_str(),key.c_str(),NULL);
}

string ConfigFile::getValue(const string& section, const string& key, const string& value)
{
    string val = getValue(section, key);
    if(val == "")
    {
        setValue(section,key,value);
        return value;
    }
    return val;
}

void ConfigFile::setValue(const string& section, const string& key, const string& value, const string& comment)
{
    // Check if value already exists in file... pure to prevent writes
    string t = getValue(section, key);
    if (t == value)
        return;

    // The value is different to what is in the file so we write it
    if(comment == "")
        ini->SetValue(section.c_str(), key.c_str(), value.c_str());
    else
        ini->SetValue(section.c_str(), key.c_str(), value.c_str(),comment.c_str());

    // A change has been made.
    changed=true;
}

vector<string> ConfigFile::getValues(const string& section, const string& key)
{
    vector<string> out;
    // get all values of a key with multiple values
    CSimpleIniA::TNamesDepend values;
    ini->GetAllValues(section.c_str(), key.c_str(), values);
    values.sort(CSimpleIniA::Entry::LoadOrder());
    // output all of the items
    CSimpleIniA::TNamesDepend::const_iterator i;
    for (i = values.begin(); i != values.end(); ++i)
    {
        out.push_back(i->pItem);
    }
    return out;
}

vector<string> ConfigFile::getKeys(const string& section)
{
    vector<string> out;
    // get all values of a key with multiple values
    CSimpleIniA::TNamesDepend values;
    ini->GetAllKeys(section.c_str(), values);
    values.sort(CSimpleIniA::Entry::LoadOrder());
    // output all of the items
    CSimpleIniA::TNamesDepend::const_iterator i;
    for (i = values.begin(); i != values.end(); ++i)
    {
        out.push_back(i->pItem);
    }
    return out;
}

vector<string> ConfigFile::getSections()
{
    vector<string> out;
    CSimpleIniA::TNamesDepend sections;
    ini->GetAllSections(sections);
    sections.sort(CSimpleIniA::Entry::LoadOrder());
    CSimpleIniA::TNamesDepend::const_iterator i;
    for (i = sections.begin(); i != sections.end(); ++i)
    {
        out.push_back(i->pItem);
    }
    return out;
}

Penjin::ERRORS ConfigFile::getError(const int& error)
{
    /*    SI_FAIL     = -1,   //!< Generic failure
    SI_NOMEM    = -2,   //!< Out of memory error
    SI_FILE     = -3    //!< File error (see errno for detail error)*/
    if(error<0)
    {
        if(error==-1)
            return PENJIN_ERROR;
        else if(error==-2)
            return PENJIN_ERROR;
        else
            return PENJIN_FILE_NOT_FOUND;
    }
    return PENJIN_OK;
}

bool ConfigFile::hasChanged()
{
    return changed;
}
