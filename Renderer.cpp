/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
#include "Renderer.h"
#include "Timer.h"
#include "RenderObject.h"
using Penjin::Renderer;
using Penjin::Timer;
using Penjin::RenderObject;

Renderer::Renderer() :  bpp(0), fps(60), fullScreen(false),clearColour(BLACK), drawColour(WHITE), drawWidth(1), timer(NULL)
{
    //ctor
    timer = new Timer;
    setFrameRate(fps);
}

Renderer::~Renderer()
{
    //dtor
    delete timer;
}

void Renderer::setBitsPerPixel(const int& bpp)
{
    this->bpp = bpp;
}

void Renderer::setFullscreen(const bool& fs)
{
    fullScreen = fs;
}

void Renderer::setClearColour(const Colour& c)
{
    clearColour = c;
}

void Renderer::setDrawColour(const Colour& c)
{
    drawColour = c;
}

void Renderer::setDrawWidth(const int & w)
{
    drawWidth = w;
}

void Renderer::setFrameRate(const uint& fps)
{
    timer->setFramesPerSecond(fps);
    this->fps = fps;
}

void Renderer::frameLimiter()
{
    float sleepTime = timer->getScaler() - timer->getTicks();
    static float diff = 0; // value compensating the precision loss due to float-int conversions
    if (sleepTime > 0)
    {
        diff += sleepTime - (int)sleepTime;
        timer->delay((int)sleepTime + (int)diff);
        while ((int)diff > 0)
            --diff;
    }
}

void Renderer::queueRenderObject(RenderObject* obj)
{
    if(obj)
        rendObjs.push_back(obj);
}

void Renderer::renderQueue()
{
    // Currently we just render the queued items...
    // The eventual goal is to cull items that don't need drawing before hand.
    for(uint i = 0; i < rendObjs.size(); ++i)
        rendObjs.at(i)->render();

    rendObjs.clear();
}
