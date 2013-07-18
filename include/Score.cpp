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
#include "Score.h"
using Penjin::Score;

Score::Score()
{
	score = 0;
	lastScore = 0;
	multiplier = 1;
}

int Score::getDifference()const
{
	return score-lastScore;
}

int Score::getMultiplier()const
{
	return multiplier;
}

int Score::getScore()const
{
	return score;
}

void Score::increaseMultiplier()
{
	++multiplier;
}

void Score::changeScore(const int& points)
{
	score += (points * multiplier);
}

void Score::resetScore()
{
	score = 0;
}

void Score::setMultiplier(const int& mult)
{
	multiplier = mult;
}

void Score::storeScore()
{
	lastScore = score;
}

