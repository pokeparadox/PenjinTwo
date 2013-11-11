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
#include "TextFile.h"
//#include "ErrorHandler.h"
using Penjin::TextFile;

void TextFile::append(CRstring data)
{
	docData.push_back(data);
}

void TextFile::editLine(CRuint line,CRstring newData)
{
	docData[line] = newData;
}

int TextFile::findLine(CRstring target)
{
	for(int i = docData.size()-1; i >= 0; --i)
	{
		//if(strstr(docData[i].c_str(),target.c_str()))
		if(docData.at(i).find(target) != string::npos)
		{
			return i;
		}
	}
	return PENJIN_ERROR;
}

void TextFile::clear()
{
    docData.clear();
}


Penjin::ERRORS TextFile::load(const vector<string>& lines)
{
    docData = lines;
    return PENJIN_OK;
}

Penjin::ERRORS TextFile::load(CRstring file)
{
    //ErrorHandler* eMan = ErrorMan::getInstance();
    #if defined (PLATFORM_WII)
        FILE *f = fopen ((Penjin::getWorkingDirectory() + file).c_str(), "rb");
        // can't find file
        if (f == NULL)
           return PENJIN_FILE_NOT_FOUND;
        else
        { // Otherwise if it was fine, we can continue.
            char temp [1024];
            string t2 = "NULL";
            int line = 0;
            clear();
            while (fgets (temp, 1024, f))
            {
                t2=temp;
                t2+="\n";
                if(temp == "\n")
                    break;
                docData.push_back(t2);
                ++line;
            }
            fclose(f);
            return PENJIN_OK;
        }
        return PENJIN_ERROR;
	#else
        ifstream ifile(file.c_str());//load infile

        if(!ifile.is_open())
        {
            //eMan->print(PENJIN_FILE_NOT_FOUND, "TextFile: " + file);
            return PENJIN_FILE_NOT_FOUND;
        }

        clear();

        string temp = "NULL";
        while(ifile.good())
        {
            getline(ifile,temp);
            docData.push_back(temp);
        }
        if(ifile.is_open())
        {
            ifile.close();
            fileName = file;
            return PENJIN_OK;
        }
        //eMan->print(PENJIN_ERROR, "TextFile::load");
        return PENJIN_ERROR;
    #endif
}

Penjin::ERRORS TextFile::save(CRstring file)
{
    //ErrorHandler* eMan = ErrorMan::getInstance();
    #if defined(PLATFORM_WII)
        FILE *f = fopen ((Penjin::getWorkingDirectory() + file).c_str(), "wb");
        if (f == NULL)
          return PENJIN_UNABLE_TO_SAVE;
        else
        {
            size_t size = docData.size();
            for (size_t i = 0; i < size; ++i)
            {
                if(i < size-1)
                    fputs ((docData.at(i) + "/n").c_str() ,f);
                else
                    fputs (docData.at(i).c_str() ,f);
            }
           fclose(f);
           return PENJIN_OK;
        }
        return PENJIN_ERROR;
    #else
        ofstream ofile(file.c_str());//save ofile
        if(!ofile.is_open())
        {
            //eMan->print(PENJIN_UNABLE_TO_SAVE, "TextFile: " + file);
            return PENJIN_UNABLE_TO_SAVE;
        }
        size_t size = docData.size();
        for (size_t i = 0; i < size; ++i)
        {
                ofile << docData[i];

                if(i < docData.size()-1)
                {
                    ofile << "\n";
                }
        }
        if(ofile.is_open())
        {
            ofile.close();
            fileName = file;
            return PENJIN_OK;
        }
        //eMan->print(PENJIN_ERROR, "TextFile::save");
        return PENJIN_ERROR;
	#endif
}

string TextFile::getLine(CRuint line)
{
	if(line<docData.size())
		return docData[line];
	return "PENJIN_INVALID_INDEX";
}

void TextFile::search(CRstring target)
{
}

void TextFile::viewDoc()
{
	for (size_t i = 0; i < docData.size(); ++i)
		cout << "L:" << i << " " <<this->docData[i] << endl;
}

