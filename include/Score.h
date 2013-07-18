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
#ifndef SCORE_H
#define SCORE_H

#include "Object.h"

namespace Penjin
{
    class Score : public Object
    {
        public:
            Score();
            int getScore()const;					    //	returns the current score
            void changeScore(const int& points);		//	change score by set number of points
            void setMultiplier(const int& mult);	    //	set a value for a score multiplier
            int getMultiplier()const;				//	gets the current multiplier
            void increaseMultiplier();		    //  increase multiply by 1
            void resetScore();			        //	Resets the score
            void storeScore();			        //	Stores the current score
            int getDifference()const;			    //	Returns the difference
        private:
            int score;
            int multiplier;
            int lastScore;
    };
}


#endif	//	SCORE_H
