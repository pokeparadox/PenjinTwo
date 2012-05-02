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
*/
/***************************************************************************************************
*   \file IniFile is a class to handle the reading of simple ini files.
*   \author Kevin Winfield-Pantoja
*/

#include "IniFile.h"
#include "StringUtility.h"
using Penjin::IniFile;

IniFile::IniFile() : currentSec(0), changed(false)
{
    //ctor
}

IniFile::~IniFile()
{
    //if(changed)
    save(this->fileName);
    //dtor
    clear();
}
void IniFile::clear()
{
    TextFile::clear();
    iniData.clear();
    changed=true;
}

Penjin::ERRORS IniFile::load(const string& fileName)
{
    // clear out existing data
    clear();
    //  Load the RAW text file
    ERRORS e = TextFile::load(fileName);

    //  If there was a problem...
    if(e != PENJIN_OK)
        return e;

    //iniData.resize(1);
    //  Otherwise we continue and look for sections and comments
    for(int i = 0; i < docData.size(); ++i)
    {
        // process the RAW string
        processLine(getLine(i));
    }
    changed = false;

    //  If we have loaded the raw txtfile we can clear the raw data.
    TextFile::clear();
    return e;
}

Penjin::ERRORS IniFile::save(const string& fileName)
{
    // TODO: Check if the file contents actually differe from what is stored
    //  If there are no changes we just return PENJIN_OK.
    // For time being we will just save everytime...

    // We need to clear the TextFile
    TextFile::clear();
    // We will first run through the sections
    for(int s = 0; s < iniData.size(); ++s)
    {
        //  If there are more than one subsections
        if(iniData.at(s).sub.size() > 1)
        {
            //  Then we need to run through any subSections
            for(int ss = 0; ss < iniData.at(s).sub.size(); ++ss)
            {
                writeSection( s, ss);
            }
        }
        else
        {
            // If we get here it means there are no subsections so we just use the name only
            writeSection(s , 0);
        }
    }

    return TextFile::save(fileName);
}

void IniFile::writeSection(int index, int subSecIndex)
{
    if(index >= iniData.size())
        return;

    int ID;

    string section = iniData.at(index).name;
    if(subSecIndex >= iniData.at(index).sub.size())
        ID = -1;
    else
        ID =  iniData.at(index).sub.at(subSecIndex).ID;

    //  First we need to create the Header of the section
    if(ID == -1)
        TextFile::append("[" + section + "]");
    else
        TextFile::append("[" + section + "_"
                        + StringUtility::leadingZero(ID)+ "]");

    //  Now we need to write each line under the header
    for (int i = 0; i < iniData.at(index).sub.at(subSecIndex).lines.size(); ++i)
    {
        //  We check if there are subLines
        if(iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.size() > 1)
        {
            // We need to run through SubLines
            for(int j = 0; j < iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.size(); ++j)
            {
                string key = iniData.at(index).sub.at(subSecIndex).lines.at(i).key;
                ID = iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.at(j).ID;
                string value =  iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.at(j).value;
                string comment =  iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.at(j).comment;
                writeLine(key, ID, value, comment);
            }
        }
        else
        {
            // We just need to write one line
                string key = iniData.at(index).sub.at(subSecIndex).lines.at(i).key;
                //ID = iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.at(j).ID;
                string value =  iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.at(0).value;
                string comment =  iniData.at(index).sub.at(subSecIndex).lines.at(i).sub.at(0).comment;
                writeLine(key,-1, value, comment);
        }
    }
}

void IniFile::writeLine(string key, int ID, string value, string comment)
{
    if(comment != "")
        comment = ";  " + comment;

    if(ID=-1)
        TextFile::append(key + " = " + value + comment);
    else
        TextFile::append(key + StringUtility::leadingZero(ID) + " = " + value + comment);
}

void IniFile::processLine(string raw)
{
    int ID=-1;

    // check for any comments
    string comment = getComment(raw);
    // check for a section
    string section = getSection(raw);
    if(section!="")
    {
        // if we have a section name we can't have any other info
        ID = getID(section);

        //  If we have a valid ID we can separate the Section name
        if(ID != -1)
            section = getKey(section,'_');

        // now create this section
        createSection(section,ID);
        return;
    }

    //  If we get here we see if there is a Key/Value pair
    string key = getKey(raw);
    string value = getValue(raw);

    // Removes leading and trailing spaces
    key = clean(key);
    value = clean(value);

    if(key!="" && value !="")
    {
        ID = getID(key);

        if(ID != -1)
            key = getKey(key, '_');

        setValue(key, ID, value, comment);
        return;
    }
}

string IniFile::clean(string in)
{
    in = StringUtility::removeLeadingSpaces(in);
    in = StringUtility::removeTrailingSpaces(in);
    in = StringUtility::stripLineEndings(in);
    return in;
}

string IniFile::getComment(string raw)
{
    return getValue(raw,';');
}

int IniFile::getID(string raw)
{
//  Check if there is an ID
    string t = getValue(raw,'_');
    if(t != "")
    {
        return StringUtility::stringToInt(t);
    }
    return -1;
}

vector<string> IniFile::getSections()
{
    vector<string> out;
    for(int i = 0;i < iniData.size(); ++i)
    {
        out.push_back(iniData.at(i).name);
    }
    return out;
}

vector<string> IniFile::getKeys(const string& section)
{
    size_t found = findSection(section);
    vector<string> out;
    if(found != -1)
    {
        for(int i = 0;i < iniData.at(found).sub.at(0).lines.size(); ++i)
        {
            out.push_back(iniData.at(found).sub.at(0).lines.at(i).key);
        }

    }
    return out;
}

bool IniFile::hasChanged()
{
    return changed;
}


string IniFile::getValue(const string& sec, const string& key)
{
    size_t foundSec = findSection(sec);
    if(foundSec != -1)
    {
        size_t foundKey = findKey(foundSec, key);
        if(foundKey != -1)
        {
            return iniData.at(foundSec).sub.at(0).lines.at(foundKey).sub.at(0).value;
        }
    }
    return "";
}

string IniFile::getValue(const string& section, const string& key, const string& value)
{
    string val = getValue(section,key);
    if(val != "")
        return val;

    setValue(section,-1,key,-1,value);
    return value;
}

string IniFile::getSection(string raw)
{
    //  Check for section
    size_t pos,pos2;
    pos = raw.find('[');
    pos2 = raw.find(']');
    if(pos != raw.npos && pos2 != raw.npos)
    {
        return raw.substr(pos+1,pos2-1);
    }
    return "";
}

string IniFile::getKey(string raw, char sep)
{
    vector<string> tokens;
    string del;
    del.push_back(sep);
    StringUtility::tokenise(raw,tokens,del);
    if(tokens.size() > 0)
        return tokens.at(0);
    return "";
}

string IniFile::getValue(string raw, char sep)
{
    vector<string> tokens;
    string del;
    del.push_back(sep);
    StringUtility::tokenise(raw,tokens,del);
    if(tokens.size() > 1)
        return tokens.at(1);
    return "";
}

void IniFile::createSection(string sec, int ID)
{
    // check if section with this name exists in current document
    for(int i = 0; i < iniData.size(); ++ i)
    {
        if(sec == iniData.at(i).name)
        {
            //  Now we have found the section we check if there is a SubSection with the ID
            for(int j = 0; j < iniData.at(i).sub.size(); ++j)
            {
                // if we find the ID
                if(ID == iniData.at(i).sub.at(j).ID)
                {
                    currentSecID = j;
                    // if we find the section we set currentsec to i and return
                    currentSec = i;
                    return;
                }
            }
            //  Getting to here means we have the name of the section
            // BUT we don't have the sub ID
            // We need to create the ID
            SubSection ss;
            ss.ID = ID;
            iniData.at(i).sub.push_back(ss);
            currentSec = i;
            currentSecID = iniData.at(i).sub.size()-1;
            return;
        }
    }

    //  Here we have not found the section or ID so we add a new section
    IniSection s;
    s.name = sec;

    SubSection ss;
    ss.ID = ID;
    s.sub.push_back(ss);
    iniData.push_back(s);
    currentSec = iniData.size()-1;
    currentSecID = iniData.at(currentSec).sub.size()-1;
}


size_t IniFile::findSection(string sec)
{
    // check if section with this name exists in current document
    for(int i = 0; i < iniData.size(); ++ i)
    {
        if(sec == iniData.at(i).name)
        {
            return i;
        }
    }
    return -1;
}

size_t IniFile::findKey(size_t sec, string key)
{
    // check if section with this name exists in current document
    for(int i = 0; i < iniData.at(sec).sub.at(0).lines.size(); ++ i)
    {
        if(key == iniData.at(sec).sub.at(0).lines.at(i).key)
        {
            return i;
        }
    }
    return -1;
}

void IniFile::setValue(const string& section, const int& ID, const string& key, const int& keyID, const string& value, const string& comment)
{

    createSection(section,ID);
    setValue(key,keyID,value,comment);
}

void IniFile::setValue(const string& section, const string& key, const string& value, const string& comment)
{
    createSection(section);
    setValue(key,-1,value,comment);
}

void IniFile::setValue(string k, int ID, string v, string c)
{
    //  We check if we have a Section to put Keys and Values into
    if(iniData.empty())
        createSection("Default");

    //  If we are here we can run through the lines in this section
    for(int j =0; j < iniData.at(currentSec).sub.at(currentSecID).lines.size();++j)
    {
        //  We have found the key
        if(iniData.at(currentSec).sub.at(currentSecID).lines.at(j).key == k)
        {
            //  check for id
            for(int k = 0; k < iniData.at(currentSec).sub.at(currentSecID).lines.at(j).sub.size(); ++k)
            {
                if(iniData.at(currentSec).sub.at(currentSecID).lines.at(j).sub.at(k).ID == ID)
                {
                    //  If we are here we can set the value and comment
                    iniData.at(currentSec).sub.at(currentSecID).lines.at(j).sub.at(k).value = v;
                    iniData.at(currentSec).sub.at(currentSecID).lines.at(j).sub.at(k).comment = c;
                    return;
                }
            }
            //  Reaching here means we need to add a SubLine
            SubLine sl;
            sl.comment = c;
            sl.ID = ID;
            sl.value = v;
            iniData.at(currentSec).sub.at(currentSecID).lines.at(j).sub.push_back(sl);
            return;
        }
    }
    //  Reaching here that the Key does not exist so we add the key
    IniLine in;
    in.key = k;
    SubLine sl;
    sl.comment = c;
    sl.ID = ID;
    sl.value = v;
    in.sub.push_back(sl);
    iniData.at(currentSec).sub.at(currentSecID).lines.push_back(in);
    return;
}


