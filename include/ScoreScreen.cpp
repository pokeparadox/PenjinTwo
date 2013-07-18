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
#include "ScoreScreen.h"
#include "HiScore.h"
#include "Text.h"
#include "StringUtility.h"
using Penjin::ScoreScreen;
using Penjin::HiScore;
using Penjin::Text;

ScoreScreen::ScoreScreen()
{
    //ctor
	scoreFile = "scores.txt";
	nameEntry = true;
	textStrings[1] = "";
	score = 0;
	currentLetter = 'A';
}

ScoreScreen::ScoreScreen(CRstring scoreFile)
{
    this->scoreFile = scoreFile;
//    firstPass = true;
	nameEntry = true;
	textStrings[1] = "";
	score = 0;
	currentLetter = 'A';
}

void ScoreScreen::init()
{
    //  First load scores
    if(scores->load(scoreFile) != PENJIN_OK)
	{
	    scores->initialiseTables();
        scores->save(scoreFile);
	}
	textStrings[1] = scores->getName(scores->getLastNameIndex());
	//scores.setBoundaries(bounds);
	// Create a nice starfield effect
	/*emit.resize(3);
	emit[0].setMax(bounds.w/bounds.h*200);
	emit[0].setBoundaries(bounds);
	emit[0].setPosition(Vector2di(bounds.w*0.5f,bounds.h*0.5f));
	emit[0].setLifeTime(3000);
	emit[0].setMaxVelocity(Vector2df(2.8f,2.8f));
	emit[0].setDeviation(0.01f);
    emit[1].setMax(bounds.w/bounds.h*100);
	emit[1].setBoundaries(bounds);
	emit[1].setPosition(Vector2di(bounds.w*0.5f,bounds.h*0.5f));
	emit[1].setLifeTime(1500);
	emit[1].setMaxVelocity(Vector2df(3.8f,3.8f));
	emit[1].setDeviation(0.05f);
    emit[1].setColour(Colour(YELLOW));
    emit[2].setMax(bounds.w/bounds.h*50);
	emit[2].setBoundaries(bounds);
	emit[2].setPosition(Vector2di(bounds.w*0.5f,bounds.h*0.5f));
	emit[2].setLifeTime(1100);
	emit[2].setMaxVelocity(Vector2df(4.5f,4.5f));
	emit[2].setDeviation(0.05f);
    emit[2].setColour(Colour(128,128,255));

    /// PreUpdate emitters
    for(int i = emit.size()-1;i >=0; --i)
        emit[i].advanceUpdate(120);
*/
    /// setup Text positions
    textStrings[0] = "   ";
    textStrings[2] = "OK?";
    textStrings[3] = "Game Over!";
    float t = 0.2f;
    Text* text = TextMan::getInstance();
    text->setDimensions(getDimensions());
    for(int i = 3; i >= 0; --i)
    {
        text->print(textStrings[i]);
        textPositions[i] = text->getDimensions();
        textPositions[i] = centralise(textPositions[i], getDimensions());
        textPositions[i].y = t * getHeight();
        t+=0.2f;
    }
    if(nameEntry)
    {
        if(score <= scores->getScore(9))
            nameEntry = false;
    }
}

ScoreScreen::~ScoreScreen()
{
    //dtor
    scores->save(scoreFile);
}

void ScoreScreen::charInput(uchar l)
{
    if(nameEntry && StringUtility::isLetter(l) && textStrings[1].length()<3)
        textStrings[1]+=l;
}

void ScoreScreen::update()
{
    /*for(int i = emit.size()-1; i >=0; --i)
        emit.at(i).update();
*/
    if(textStrings[1].length()>3)
    {
        //	turn name entry off
        nameEntry = false;

        //	Get rid of last letter
        textStrings[1][3]=0;

        //	Enter highscore into table
        scores->nameEntry(StringUtility::upper(textStrings[1]), score);
        textStrings[1].clear();
    }
}


void ScoreScreen::render()
{
/*for(int i = emit.size()-1; i >=0; --i)
        emit[i].render(screen);
*/
    if(nameEntry)
    {
        Text* text = TextMan::getInstance();
        /// Display Name entry mode
        text->setColour(YELLOW);
        text->setPosition(textPositions[0]);
        if(textStrings[1].size()<3)
            textStrings[0][0] = currentLetter;
        else
            textStrings[0][0] = '?';
        text->print(textStrings[0]);
        text->setPosition(textPositions[1]);
        text->setColour(WHITE);
        if(textStrings[1].size()<3)
            text->print(textStrings[1]);
        else
            text->print(textStrings[1] + " " + textStrings[2]);
        text->setPosition(textPositions[2]);
        text->setColour(BLUE);
        text->print((int)score);
        text->setPosition(textPositions[3]);
        text->setColour(ORANGE);
        text->print(textStrings[3]);
    }
    else
    {
        /// Show Hi-Score table.
        scores->render();
    }
}

Vector2di ScoreScreen::centralise(const Vector2di& a,Vector2di b)
{
    b-=a;
    b/=2;
    return b;
}
