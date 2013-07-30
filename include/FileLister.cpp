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
#include "FileLister.h"
#include "StringUtility.h"
#include "DirMenuItem.h"

using Penjin::FileLister;
using Penjin::DirMenuItem;
FileLister::FileLister()
{
    //ctor
    char* temp;
    temp = new char[_MAX_PATH];
    temp = getcwd(temp,_MAX_PATH);
    workingDir = temp;
    delete [] temp;
    createListing();
    folderDepth = -1;
    checkFolderDepth = true;
}

FileLister::FileLister(CRstring startDir)
{
    workingDir = startDir;
    createListing();
    folderDepth = -1;
    checkFolderDepth = true;
}

FileLister::~FileLister()
{
    //dtor
}

void FileLister::createListing()
{
    DIR* dir = NULL;
    dirent* dirEnt;
    dir = opendir(workingDir.c_str());
    if(!dir)
        return;

    listing.clear();
    listingTypes.clear();
    listing.push_back(workingDir);
    listingTypes.push_back(PATH);
    while((dirEnt = readdir(dir)))
    {
        if(filters.size() == 0)
        {
            int type = -1;
            string choice = dirEnt->d_name;
            #ifdef _WIN32
                struct stat fileStat;
                stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                if(fileStat.st_mode & DT_DIR)
                    type=DT_DIR;
                else if(fileStat.st_mode & DT_REG)
                    type=DT_REG;
                else
                    type=UNKNOWN;
            #else
                if(dirEnt->d_type == DT_DIR)
                    type=DT_DIR;
                else if(dirEnt->d_type == DT_REG)
                    type=DT_REG;
                else
                    type=UNKNOWN;
            #endif
            listing.push_back(choice);
            listingTypes.push_back(type);
        }
        else
        {
            for(int f = filters.size()-1; f>=0; --f)
            {
                int type = -1;
                string choice = dirEnt->d_name;
                #ifdef _WIN32
                    struct stat fileStat;
                    stat(string(workingDir + "/" + dirEnt->d_name).c_str(),&fileStat);
                    if(fileStat.st_mode & DT_DIR)
                        type=DT_DIR;
                    else if(fileStat.st_mode & DT_REG)
                        type=DT_REG;
                    else
                        type=UNKNOWN;
                #else
                    if(dirEnt->d_type == DT_DIR)
                        type=DT_DIR;
                    else if(dirEnt->d_type == DT_REG)
                        type=DT_REG;
                    else
                        type=UNKNOWN;
                #endif
                if( (filters.at(f) == "DIR" && type == DT_DIR) || choice.find("." + filters.at(f)) != choice.npos)
                {
                    listing.push_back(choice);
                    listingTypes.push_back(type);
                }
            }
        }
    }
    closedir(dir);
}

void FileLister::createDisplay()
{
    if(listing.empty())
        createListing();

    clear();
    #ifdef _DEBUG
        cout << "Size: " << listing.size() << endl;
    #endif
    for(uint i = 0; i<listing.size(); ++i)
    {
        DirMenuItem* dir = new DirMenuItem;
        dir->setText(listing.at(i));
        dir->setDirType(listingTypes.at(i));
        add(dir);
        #ifdef _DEBUG
        cout << "at(" << i << ") - " <<listing.at(i) << endl;
        #endif
    }
}

string FileLister::getSelected()
{
    return listing.at(selection);
}

string FileLister::enter()
{
    string t = getSelected();
    if(t == "..")       //  Same as goUp()
        goUp();
    else if(t == ".")   //  This directory.
        return t;
    else if(((DirMenuItem*)widgets.at(selectionConfirm()))->getDirType() == DT_DIR)
    {
        #ifdef _WIN32
            workingDir+= ("\\" + t);
        #else
            workingDir+= ("/" + t);
        #endif
        createListing();
        clear();
        ++folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
    #ifdef _WIN32
        return getPath() + ("\\" + t);
    #else
        return getPath() + ("/" + t);
    #endif
}

void FileLister::goUp()
{
    if(folderDepth>=0 || !checkFolderDepth)
    {
        workingDir = StringUtility::getParentDirectory(workingDir);
        size_t back = workingDir.size()-1;
        if(workingDir.at(back) == '/' || workingDir.at(back) == '\\')
            workingDir.resize(back);
        createListing();
        clear();
        --folderDepth;
        #ifdef _DEBUG
        cout << "FD: " << folderDepth << endl;
        #endif
    }
}

void FileLister::update()
{
    if(listing.empty())
        createListing();
    ((Menu*)this)->update();
}

void FileLister::render()
{
    if(empty())
        createDisplay();

    ((Menu*)this)->render();
}
