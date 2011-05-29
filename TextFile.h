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
#ifndef TEXTDOC_H
#define TEXTDOC_H

#include "PenjinFileObject.h"

#include <string>
#include <vector>
#ifdef PLATFORM_WII
    #include "Penjin.h"
#else
    #include <fstream>
#endif
#include <iostream>
using namespace std;

//#include "ErrorHandler.h"
#include "PenjinErrors.h"
#include "PenjinTypes.h"
using namespace PenjinErrors;

class TextFile : public PenjinFileObject
{
    public:
        TextFile()
        {
            clear();
        }
        virtual ~TextFile(){clear();}
        uint size(){return docData.size();}
        virtual PENJIN_ERRORS load(CRstring file);					//	Load a plain text file
        PENJIN_ERRORS load(const vector<string>& lines);           //  Load a doc from raw lines
        virtual PENJIN_ERRORS save(CRstring file);					//	Save a plain text file
        void search(CRstring target);				//	Search for a string in the doc
        void editLine(CRint line, CRstring newData);//	replace a line of data with new data
        string getLine(CRint line);				//	get the string data of the line
        void viewDoc();							//	View an outline of the doc
        void clear();							//	Clear data out of doc.
        void append(CRstring data);				//	adds a string to the document
    private:
        int findLine(CRstring target);
        vector <string> docData;
};

#endif	//	TEXTDOC_H
