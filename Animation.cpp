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
#include "Animation.h"
using Penjin::Animation;

Animation::Animation(): numLoops(-1), firstLoops(-1), playMode(pmNormal), hasFinishedVal(false), reachedEnd(false)
{
	Timer::setMode(THIRTY_FRAMES);
	start();
}

Animation::~Animation()
{

}

void Animation::setLooping(CRbool loop)
{
    if(loop)
        numLoops = firstLoops = -1;
    else
        numLoops = firstLoops = 0;
}

void Animation::setLooping(CRint loops)
{
    this->numLoops = firstLoops = (loops-1);
}


Penjin::PlayMode Animation::getPlayMode()
{
    return playMode;
}

void Animation::setReversePlay(CRbool reverse)
{
    if (reverse)
        playMode = pmReverse;
    else
        playMode = pmNormal;
};

void Animation::setPulsePlay(CRbool pulse)
{
    if (pulse)
        playMode = pmPulse;
    else
        playMode = pmNormal;
};

void Animation::setPlayMode(const PlayMode& m)
{
    playMode = m;
}

void Animation::update()
{
    if (not hasFinishedVal && getScaledTicks() >= 1) // has the next frame been reached?
    {
        start();
        switch (playMode)
        {
            case pmNormal:
            {
                ++activeImage;
                if (activeImage > size()-1)
                {
                    if (numLoops != 0) // looping
                    {
                        activeImage = 0;
                        if (numLoops > 0) // don't loop forever
                            --numLoops;
                    }
                    else
                    {
                        activeImage = size()-1;
                        hasFinishedVal = true;
                    }
                }
                break;
            }
            case pmReverse:
            {
                --activeImage;
                if (activeImage < 0)
                {
                    if (numLoops != 0) // looping
                    {
                        activeImage = size()-1;
                        if (numLoops > 0)
                            --numLoops;
                    }
                    else
                    {
                        activeImage = 0;
                        hasFinishedVal = true;
                    }
                }
                break;
            }
            case pmPulse:
            {
                if (reachedEnd) // play backwards (phase 2)
                {
                    --activeImage;
                    if (activeImage < 0)
                    {
                        if (numLoops != 0)
                        {
                            reachedEnd = false;
                            activeImage = min((size_t)1,size()-1); // set to second frame so we don't play the first frame two times in a row
                            if (numLoops > 0)
                                --numLoops;
                        }
                        else
                        {
                            activeImage = 0;
                            hasFinishedVal = true;
                            reachedEnd = false;
                        }
                    }
                }
                else // play forwards (phase 1)
                {
                    ++activeImage;
                    if (activeImage > size()-1)
                    {
                        activeImage = max((int)size()-2,0); // set to penultimate frame so we don't play the last one two times in a row
                        reachedEnd = true;
                    }
                }
                break;
            }
        }
    }
}

bool Animation::hasFinished()
{
    return hasFinishedVal;
}

void Animation::rewind()
{
    if (playMode == pmReverse)
        activeImage = size()-1;
    else
        activeImage = 0;
    numLoops = firstLoops;
    hasFinishedVal = false;
    reachedEnd = false;
    start();
}
