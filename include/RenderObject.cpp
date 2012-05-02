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
#include "GFX.h"
#include "RenderObject.h"
using Penjin::RenderObject;
RenderObject::RenderObject()
{
    //ctor
}

RenderObject::~RenderObject()
{
    //dtor
}

void RenderObject::queueRender()
{
    Renderer* gfx = GFX;
    Vector2d<float> p = getScaledPosition();
    //  Check if screen position is within the resolution
    //(Allowing for scrolling something in from the left)
    if(p.x < gfx->getWidth() && p.y < gfx->getHeight() && p.x > -gfx->getWidth() && p.y > -gfx->getHeight())
        gfx->queueRenderObject(this);
}

