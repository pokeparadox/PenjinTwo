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
#ifndef SCORESCREEN_H
#define SCORESCREEN_H

//#include "HiScore.h"
#include "Window.h"
//#include "Emitter.h"
//#include "Text.h"

#include <vector>
using std::vector;

namespace Penjin
{
    class HiScore;

    class ScoreScreen : public Window
    {
        public:
            ScoreScreen();
            ScoreScreen(const string& scoreFile);
            virtual ~ScoreScreen();


            void init();
            virtual void update();
            virtual void render();


            /// ScoreScreen specific stuff
            void setScore(const unsigned int& score){this->score=score;}         //  Set the potential hi score
            void setNameEntry(const bool& ne){nameEntry = ne;}           //  Name entry mode or table display mode
            bool inNameEntryScreen()const{return nameEntry;}
            void setScoreFile(const string& file){scoreFile = file;}

            //  Input functions
            void charUp()
            {
                if(nameEntry)
                {
                    if(currentLetter < 'Z')
                        ++currentLetter;
                    else if(currentLetter == 'Z')
                        currentLetter = 'A';
                }
            }
            void charDown()
            {
                if(nameEntry)
                {
                    if(currentLetter > 'A')
                        --currentLetter;
                    else if(currentLetter == 'A')
                        currentLetter = 'Z';
                }

            }
            void charInput()
            {
                if(nameEntry)
                    textStrings[1]+=currentLetter;
            }

            void charInput(unsigned char l);

            void charDelete()
            {
                if(textStrings[1].size() && nameEntry)
                    textStrings[1].erase( textStrings[1].begin() + textStrings[1].size()-1 );
            }

        private:
            Vector2d<int> centralise(const Vector2d<int>& a, Vector2d<int> b);
            //Text text;
            Vector2d<int> textPositions[4];
            string textStrings[4];
            //vector<Emitter> emit;
            uint score;
            HiScore* scores;
            bool nameEntry;
            string scoreFile;
            char currentLetter;
    };
}

#endif // SCORESCREEN_H
