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
#include "TextFile.h"
#include "ErrorHandler.h"

void TextFile::append(CRstring data)
{
	docData.push_back(data);
}

void TextFile::editLine(CRint line,CRstring newData)
{
	docData[line] = newData;
}

int TextFile::findLine(CRstring target)
{
	for(int i = docData.size()-1; i >= 0; --i)
	{
		if(strstr(docData[i].c_str(),target.c_str()))
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


PENJIN_ERRORS TextFile::load(const vector<string>& lines)
{
    docData = lines;
    return PENJIN_OK;
}

PENJIN_ERRORS TextFile::load(CRstring file)
{
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
            return PENJIN_FILE_NOT_FOUND;
        }

        clear();

        string temp = "NULL";
        vector <string> tStrings;
        while(ifile.good())
        {
            getline(ifile,temp);
            temp+="\n";
            if(temp == "\n")
                break;
            docData.push_back(temp);
        }
        if(ifile.is_open())
        {
            ifile.close();
            return PENJIN_OK;
        }
        return PENJIN_ERROR;
    #endif
}

PENJIN_ERRORS TextFile::save(CRstring file)
{
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
            return PENJIN_OK;
        }
        return PENJIN_ERROR;
	#endif
}

string TextFile::getLine(CRint line)
{
	if(line<(int)docData.size())
		return docData[line];
	return ErrorHandler().getErrorString(PENJIN_INVALID_INDEX);
}

void TextFile::search(CRstring target)
{
}

void TextFile::viewDoc()
{
	for (size_t i = 0; i < docData.size(); ++i)
		cout << "L:" << i << " " <<this->docData[i] << endl;
}

