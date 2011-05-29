/**
    \section LICENSE
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
**********************************************************************************************/
/**
  * \file A class which handles loading tilesheets
  * \author Kevin Winfield-Pantoja
*/
#include "ImageSheet.h"
using Penjin::ImageSheet;

ImageSheet::ImageSheet() : sheetMode(true), activeImage(0)
{
    //ctor
    setDrawWidth(1);
    setColour(MAGENTA);
}

ImageSheet::~ImageSheet()
{
    //dtor
}


Penjin::ERRORS ImageSheet::load(SDL_Surface* s)
{
    Penjin::ERRORS e = Image::load(s);
    if(surface)
        surfaces.push_back(surface);
    surface = NULL;
    return e;
}

Penjin::ERRORS ImageSheet::load(const string& file)
{
    Penjin::ERRORS e = Image::load(file);
    if(surface)
        surfaces.push_back(surface);
    surface = NULL;
    return e;
}


Penjin::ERRORS ImageSheet::load(SDL_Surface* s, CRuint xTiles, CRuint yTiles)
{
    sheetMode = true;
    // We load the raw image to surface rather than surfaces
    Penjin::ERRORS e = Image::load(s);

    // if there's problems we jump out.
    if(e != PENJIN_OK)
        return e;
    // assign clipping areas for this sheet
    return assignClipAreas(xTiles,yTiles,0,0);
}

Penjin::ERRORS ImageSheet::load(CRstring file, CRuint xTiles, CRuint yTiles)
{
    sheetMode = true;
    // We load the image file to surface rather than surfaces
    Penjin::ERRORS e = Image::load(file);

    // Get out if there's a problem
    if(e != PENJIN_OK)
        return e;
    // finally assign the clipping areas
    return assignClipAreas(xTiles,yTiles,0,0);
}

// Build clipping areas - if numTiles is 0, it will be calculated automatically
Penjin::ERRORS ImageSheet::assignClipAreas(CRuint xTiles,CRuint yTiles,CRuint skipTiles,CRuint p_numTiles)
{
    uint numTiles = p_numTiles;
    //  now we have to build the clipping areas based on the tile info we have.
    //second the width and height per tile needs to be calculated
    uint width = surface->w;
    uint height = surface->h;

    uint xTileWidth = width/xTiles;
    uint yTileWidth = height/yTiles;

    if (numTiles == 0) {
        numTiles = (xTiles * yTiles) - skipTiles;
    }

    //  Accomodate clip areas
    clipAreas.resize(numTiles);

    uint currTile = 0;
    //  Run along then down

    for(uint y = 0; y < height; y+=yTileWidth)
    {
        for(uint x = 0; x < width; x+=xTileWidth)
        {
            if (currTile >= skipTiles && (currTile-skipTiles)<numTiles) {
                //  and set the values for the clip plane
                clipAreas[currTile-skipTiles].x = x;
                clipAreas[currTile-skipTiles].y = y;
                clipAreas[currTile-skipTiles].w = xTileWidth;
                clipAreas[currTile-skipTiles].h = yTileWidth;
            }
            ++currTile;
        }
    }
    return PENJIN_OK;
}

void ImageSheet::render()
{
    if(sheetMode)
    {
        if(surface)
        {
            SDL_SetAlpha(surface, SDL_SRCALPHA, a);
            // Set up blitting area
            SDL_Rect dst;

            dst.x = position.x;
            dst.y = position.y;
            SDL_BlitSurface(surface, &clipAreas.at(activeImage), GFX::getInstance()->getSDLVideoSurface(), &dst);
        }
    }
    else
    {
        SDL_SetAlpha(surfaces.at(activeImage), SDL_SRCALPHA, a);
        // Set up blitting area
        SDL_Rect src, dst;
        src.x = surface->clip_rect.x;
        src.y = surface->clip_rect.y;
        src.w = surface->w;
        src.h = surface->h;

        dst.x = position.x;
        dst.y = position.y;
        SDL_BlitSurface(surfaces.at(activeImage), &src, GFX::getInstance()->getSDLVideoSurface(), &dst);
    }
    #ifdef _DEBUG
        // We only want to render the Rectangle to the size of one subImage
        Vector2d<int> t = getDimensions(activeImage);
        GFX::getInstance()->setDrawColour(*this);
        GFX::getInstance()->setDrawWidth(drawWidth);
        GFX::getInstance()->drawRectangle(position, t);
    #endif
}

void ImageSheet::clear()
{
    for(int i = surfaces.size()-1; i >=0; --i)
    {
        if(surfaces.at(i))
            SDL_FreeSurface(surfaces.at(i));
    }
    surfaces.clear();
    clipAreas.clear();
}

Vector2d<int> ImageSheet::getDimensions(CRuint subImage)
{
    // SheetMode means only one image
    if(sheetMode)
    {
        // This means we check clipAreas for the dimensions.
        if(subImage < clipAreas.size())
            return Vector2d<int>(clipAreas.at(subImage).w, clipAreas.at(subImage).h);
        // No clipAreas means no dimensions!
        return Vector2d<int>(0,0);
    }
    else
    {
        // This means we check surfaces for the dimensions.
        if(subImage < surfaces.size())
            return Vector2d<int>(surfaces.at(subImage)->w, surfaces.at(subImage)->h);
    }

    // If we get to here... then we have not found any dimensions!
    return Vector2d<int>(0,0);
}

void ImageSheet::setActiveImage(CRint a)
{
    if(sheetMode)
    {
        if(a<clipAreas.size())
            activeImage = a;
    }
    else
    {
        if(a<surfaces.size())
            activeImage = a;
    }
}

size_t ImageSheet::size()
{
    if(sheetMode)
        return clipAreas.size();
    else
    {
        return surfaces.size();
    }
}
