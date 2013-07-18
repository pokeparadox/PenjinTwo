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
#ifndef HISCORE_H
#define HISCORE_H

#include <string>
using std::string;
//#include <sstream>
//#include <iostream>
//#include <fstream>


#include "Text.h"
#include "TextFile.h"
#include "Window.h"
//#include "Encryption.h"
//#include "StringUtility.h"


namespace Penjin
{
    enum HI_SCORE_MODES
    {
        HSM_HIGH_TO_LOW,
        HSM_LOW_TO_HIGH
    };

    class Encryption;

    class HiScore : public Window, public TextFile
    {
        public:
            HiScore();
            HiScore(const unsigned int& numScores,const unsigned int& numInitials);

            ~HiScore();
            void clear();

            virtual ERRORS load(const string& scoreFile);
            virtual ERRORS save(const  string& scoreFile);

            void setMode(const HI_SCORE_MODES& mode);						//	Sets the sorting mode of the highscore table
            void nameEntry(string name, unsigned int score);	//	assigns a name to a specific score if it is good enough to be saved

            virtual void render();

            void initialiseTables();						//	Clears the tables, ready to use.

            unsigned int getScore(const size_t& i)const
            {
                if(i < numScores)
                    return scoreTable[i];

                return 0;
            }
            string getName(const size_t& i)const{return nameTable[i];}
            size_t getLastNameIndex()const{return lastNameIndex;}

        private:
            unsigned int numScores;
            unsigned int numInitials;
            unsigned int* scoreTable;
            string* nameTable;
            unsigned int lastNameIndex;
            HI_SCORE_MODES mode;

            Encryption* crypt;
            //string tableTitle;
    };
}

#endif	//	HISCORE_H
