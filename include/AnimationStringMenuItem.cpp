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
#include "AnimationStringMenuItem.h"

AnimationStringMenuItem::~AnimationStringMenuItem()
{

}

void AnimationStringMenuItem::init()
{
    setType(MENU_ANIM_STRING_ITEM);
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif
    dimensions.x = 0;
    dimensions.y = 0;
    isSelected = false;
    isSelectable = true;
    verticalSpacing = 0;
    horizontalOffset = 0;
    setSelectionIndicator('-');
    anim.setFrameRate(FIFTEEN_FRAMES);
    anim.setLooping(true);
    anim.setHorizontalOffset(horizontalOffset);
    text.setHorizontalOffset(horizontalOffset);
}

void AnimationStringMenuItem::update()
{
    anim.setIsSelected(isSelected);
    anim.update();

    text.setIsSelected(isSelected);
    text.update();
}

#ifdef PENJIN_SDL
    void AnimationStringMenuItem::render(SDL_Surface* screen)
    {
        anim.render(screen);
        text.render();
    }
#else
    void AnimationStringMenuItem::render()
    {
        anim.render();
        text.render();
    }
#endif

Vector2di AnimationStringMenuItem::getDimensions()
{
    Vector2di dims = anim.getDimensions();
    Vector2di txtDims = text.getDimensions();

    if(dims.x >= txtDims.x)
        dimensions.x = dims.x;
    else
        dimensions.x = txtDims.x;

    if(dims.y >= txtDims.y)
        dimensions.y = dims.y;
    else
        dimensions.y = txtDims.y;

    return dimensions;
}

PENJIN_ERRORS AnimationStringMenuItem::loadSelectionFrames(CRstring fileName,CRuint xTiles,CRuint yTiles){return anim.loadSelectionFrames(fileName, xTiles, yTiles);}
PENJIN_ERRORS AnimationStringMenuItem::loadSelectionFrame(CRstring fileName){return anim.loadSelectionFrame(fileName);}

#ifndef PENJIN_3D
    void AnimationStringMenuItem::setPosition(const Vector2df& pos)
    {
        position = pos;
        anim.setPosition(pos);
        text.setPosition(pos);
    }
#else
    void AnimationStringMenuItem::setPosition(const Vector3df& pos)
    {
        position = pos;
        anim.setPosition(pos);
        text.setPosition(pos);
    }
#endif

void AnimationStringMenuItem::centreText(CRint corr)
{
    /// Get the difference of the text and the animFrame
    Vector2di diff = text.getDimensions()-anim.getDimensions();
    diff = diff*0.5f;
    #ifdef PENJIN_3D
        text.setPosition(Vector3df(diff.x+corr,diff.y,0.0f));
    #else
        text.setPosition(Vector2df(diff.x+corr,diff.y));
    #endif
}

