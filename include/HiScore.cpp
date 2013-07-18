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
#include "HiScore.h"
#include "StringUtility.h"
#include "Encryption.h"
using namespace Penjin::StringUtility;
using Penjin::HiScore;
using Penjin::Encryption;

HiScore::HiScore()
{
	mode = HSM_HIGH_TO_LOW;
	numScores = 10;
	numInitials = 3;
	lastNameIndex = 0;
	nameTable = NULL;
	scoreTable = NULL;
	nameTable = new string[numScores];
	scoreTable = new unsigned int[numScores];
	crypt = NULL;
	crypt = new Encryption;
    setTitle("Hi Scores");
	initialiseTables();
	//ext.setRelativity(true);
	//text.setCentreText(true);

    setPosition(Vector2d<int>(120,5));
}

HiScore::HiScore(const unsigned int& numScores,const unsigned int& numInitials)
{
	mode = HSM_HIGH_TO_LOW;
	this->numScores = numScores;
	this->numInitials = numInitials;
    lastNameIndex = 0;
	nameTable = NULL;
	scoreTable = NULL;
	nameTable = new string[numScores];
	scoreTable = new unsigned int[numScores];
	crypt = NULL;
	crypt = new Encryption;
	setTitle("Hi Scores");
	initialiseTables();
//	text.setRelativity(true);

    setPosition(Vector2d<int>(120,5));
}

HiScore::~HiScore()
{
	clear();
}

void HiScore::clear()
{
    delete [] nameTable;
    delete [] scoreTable;
    delete crypt;
    nameTable = NULL;
    scoreTable = NULL;
    crypt = NULL;
}

void HiScore::initialiseTables()
{
	for (unsigned int i = 0; i < numScores; ++i)
	{
		nameTable[i] = "AAA";
		scoreTable[i] = 0;
	}
}

Penjin::ERRORS HiScore::load(const string& fileName)
{
    TextFile::clear();

	TextFile::load(fileName);
	if(!TextFile::size())
		return PENJIN_FILE_NOT_FOUND;

	for (uint i = 0; i < numScores; ++i)
		nameTable[i] = crypt->decryptBuffer(getLine(i));
	for (uint i = numScores; i < numScores*2; ++i)
		scoreTable[i-10] = stringToInt(crypt->decryptBuffer(getLine(i)));
    //  now get the index of the last enterred name
    if(TextFile::size() >numScores*2)
        lastNameIndex = stringToInt(crypt->decryptBuffer(getLine(numScores*2)));
	return PENJIN_OK;
}

/*PENJIN_ERRORS HiScore::loadScoresBinary(CRstring fileName)
{
	return PENJIN_FILE_NOT_FOUND;
}*/

void HiScore::nameEntry(string name, uint score)
{
	// get a score, then compare with the other scores
	for (uint i = 0; i < numScores; ++i)
	{
		for(uint x = 0; x < numScores; ++x)
		{
			if(mode == HSM_HIGH_TO_LOW)
			{
				//	Check which score is the highest in value
				if(score > scoreTable[x])
				{
					//	If the score is bigger then swap the bigger score into the temp value
					uint temp = scoreTable[x];
					string sTemp = nameTable[x];

					scoreTable[x] = score;
					nameTable[x] = name;

					score = temp;
					name = sTemp;
					lastNameIndex = x;
				}
			}
			else
			{
				//	Check which score is the lowest or equal in value
				if(score <= scoreTable[x] || scoreTable[x] == 0)
				{
					//	If the score is lower then swap the lower score into the temp value
					uint temp = scoreTable[x];
					string sTemp = nameTable[x];

					scoreTable[x] = score;
					nameTable[x] = name;

					score = temp;
					name = sTemp;
					lastNameIndex = x;
				}
			}
		}
	}
}


void HiScore::render()
{
    /*
    text.setPosition(centrePos.x,startPos.y);
    text.print(tableTitle + (string)" \n \n");
    for (uint i = 0; i < numScores; ++i)
    {
        text.setPosition(startPos.x, text.getPosition().y);
        text.print((int)i+1);
        text.setPosition(centrePos.x, text.getPosition().y);
        text.print(nameTable[i]);
        text.setPosition(endPos.x, text.getPosition().y);
        text.print((int)scoreTable[i]);text.print((string)" \n");	//	GP2X Spacing fix... hopefully
    }
    */
}

Penjin::ERRORS HiScore::save(CRstring fileName)
{
	clear();
	for (uint i = 0; i < numScores; ++i)
		append(crypt->encryptBuffer(nameTable[i]));
	for (uint i = 0; i < numScores; ++i)
		append(crypt->encryptBuffer(intToString(scoreTable[i])));
    append(crypt->encryptBuffer(intToString(lastNameIndex)));
	save(fileName);
	return PENJIN_OK;
}

/*PENJIN_ERRORS HiScore::saveScoresBinary(CRstring fileName)
{
	return PENJIN_FILE_NOT_FOUND;
}*/

void HiScore::setMode(const HI_SCORE_MODES& mode)
{
	this->mode = mode;
}

/*void HiScore::setBoundaries(const SDL_Rect& b)
{
    text.setBoundaries(b);
    startPos.x = b.x + (0.1f * b.w);
    startPos.y = b.y + (0.1f * b.h);
    endPos.x = b.x + (0.7f * b.w);
    endPos.y = b.y + (0.7f * b.h);
    centrePos = endPos - startPos;
    centrePos *=0.5f;
}*/
