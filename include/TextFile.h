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
#ifndef TEXTDOC_H
#define TEXTDOC_H

#include "FileObject.h"

#include <string>
#include <vector>
#ifdef PLATFORM_WII
    #include "Penjin.h"
#else
    #include <fstream>
#endif
#include <iostream>
using namespace std;

#include "Errors.h"
#include "PenjinTypes.h"
namespace Penjin
{
    class TextFile : public FileObject
    {
        public:
            TextFile()
            {
                clear();
            }
            virtual ~TextFile(){clear();}
            size_t size(){return docData.size();}
            virtual Penjin::ERRORS load(CRstring file);					//	Load a plain text file
            Penjin::ERRORS load(const vector<string>& lines);           //  Load a doc from raw lines
            virtual Penjin::ERRORS save(CRstring file);					//	Save a plain text file
            void search(CRstring target);				//	Search for a string in the doc
            void editLine(CRint line, CRstring newData);//	replace a line of data with new data
            string getLine(CRint line);				//	get the string data of the line
            void viewDoc();							//	View an outline of the doc
            virtual void clear();							//	Clear data out of doc.
            void append(CRstring data);				//	adds a string to the document
        protected:
            int findLine(CRstring target);
            vector <string> docData;
    };
}


#endif	//	TEXTDOC_H
