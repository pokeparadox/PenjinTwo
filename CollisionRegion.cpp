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
#include "CollisionRegion.h"
#include "Colour.h"

#include "NumberUtility.h"
using Penjin::CollisionRegion;
using Penjin::Colour;
CollisionRegion::CollisionRegion()
{
    //ctor
    noCollision = WHITE;
    map = NULL;
    showRect = NULL;
    region.x = 0;
    region.y = 0;
    region.w = 0;
    region.h = 0;
    pos = Vector2d<int>(0,0);
    shared = false;
}

CollisionRegion::~CollisionRegion()
{
    if(!shared)
        delete map;
    delete showRect;
}

void CollisionRegion::generateHitRegion()
{
    if (map == NULL)
        return;

    float l,t,r,b;
    r = b = 0;
    l = map->getWidth();
    t = map->getHeight();
    // starting on the bottom left, go to the top right of the image
    // determines the smallest bounding box aroudn the colliding object
    for (float I = map->getWidth()-1; I >= 0; --I)
    {
        for (float K = map->getHeight()-1; K >= 0; --K)
        {
            if (map->getPixelInFrame(Vector2d<int>(I,K),0) != noCollision)
            {
                r = max(r,I);
                b = max(b,K);
                l = min(l,I);
                t = min(t,K);
            }
        }
    }
    region.x = l;
    region.y = t;
    region.w = r-l+1;
    region.h = b-t+1;
}

Penjin::CollisionInfo CollisionRegion::hitTest(const CollisionRegion* const tester, CRbool fullShape)
{
    // TODO get collision point of contact
    Penjin::CollisionInfo i;
    i.hasCollided=false;
    i.direction=Penjin::diNONE;
    if (fullShape)
    {
        // determine overlaping area
        float xPos = max(getX(), tester->getX());
        float yPos = max(this->getY(), tester->getY());
        float xPosMax = min(this->getX() + this->getWidth(), tester->getX() + tester->getWidth());
        float yPosMax = min(this->getY() + this->getHeight(), tester->getY() + tester->getHeight());

        // check for collision
        for (float I = xPos; I <= xPosMax; ++I)
        {
            for (float K = yPos; K < yPosMax; ++K)
            {
                // if both have a collision-pixel at the same spot, we have a collision
                if (this->hitTest(I,K,true) && tester->hitTest(I,K,true))
                {
                    i.hasCollided=true;
                    i.type = this->getCollisionType(I,K,true);
                    i.direction = this->directionTest(tester,fullShape);
                    return i;
                }
            }
        }
    }
    else
    {
        // check rectangular bounds only
        if (((tester->getX() - this->getX()) < this->getWidth() && (this->getX() - tester->getX()) < tester->getWidth()) &&
            ((tester->getY() - this->getY()) < this->getHeight() && (this->getY() - tester->getY()) < tester->getHeight()))
        {
            i.hasCollided = true;
            i.direction = this->directionTest(tester,fullShape);
        }
    }
    return i;
}

Penjin::CollisionInfo CollisionRegion::hitTest(const Vector2d<int>& testPoint, CRbool fullShape)
{

}

Colour CollisionRegion::getCollisionType(float x, float y, CRbool absolute) const
{
    if (absolute)
    {
        x -= getX();
        y -= getY();
    }
    if (map == NULL)
    {
        // bounds check
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
            return noCollision;
        else
        {
            if (noCollision == Colour(WHITE))
                return BLACK;
            else
                return WHITE;
        }
    }
    else
    {
        // bounds check
        if(x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
            return noCollision;

        // add the region offset here so we can work with getX / getY as the top / left corner pixel
        return map->getPixelInFrame(Vector2d<int>(x + region.x,y + region.y),0);
    }
}  //  check what sort of collision has been made.

bool CollisionRegion::hitTest(const CollisionRegion* const tester, CRbool fullShape) const
{
    if (fullShape)
    {
        // determine overlaping area
        float xPos = max(this->getX(), tester->getX());
        float yPos = max(this->getY(), tester->getY());
        float xPosMax = min(this->getX() + this->getWidth(), tester->getX() + tester->getWidth());
        float yPosMax = min(this->getY() + this->getHeight(), tester->getY() + tester->getHeight());

        // check for collision
        for (float I = xPos; I <= xPosMax; ++I)
        {
            for (float K = yPos; K < yPosMax; ++K)
            {
                // if both have a collision-pixel at the same spot, we have a collision
                if (this->hitTest(I,K,true) && tester->hitTest(I,K,true))
                    return true;
            }
        }
        return false;
    }
    else
    {
        // check rectangular bounds only
        if (((tester->getX() - this->getX()) < this->getWidth() && (this->getX() - tester->getX()) < tester->getWidth()) &&
            ((tester->getY() - this->getY()) < this->getHeight() && (this->getY() - tester->getY()) < tester->getHeight())) return true;

        return false;
    }
}

bool CollisionRegion::hitTest(const CollisionRegion* const tester, const Vector2d<float>& posObj, const Vector2d<float>& posTester, CRbool fullShape) const
{
    float objPosX = posObj.x + this->getRegionOffsetX();
    float objPosY = posObj.y + this->getRegionOffsetY();
    float testerPosX = posTester.x + tester->getRegionOffsetX();
    float testerPosY = posTester.y + tester->getRegionOffsetY();
    if (fullShape)
    {
        // determine overlaping area
        float xPos = max(objPosX, testerPosX);
        float yPos = max(objPosY, testerPosY);
        float xPosMax = min(objPosX + this->getWidth(), testerPosX + tester->getWidth());
        float yPosMax = min(objPosY + this->getHeight(), testerPosY + tester->getHeight());

        // check for collision
        for (float I = xPos; I <= xPosMax; ++I)
        {
            for (float K = yPos; K < yPosMax; ++K)
            {
                // if both have a collision-pixel at the same spot, we have a collision
                // also substract the region offset here, because hitTest works with it
                if (this->hitTest(I - objPosX,K - objPosY,false) && tester->hitTest(I - testerPosX,K - testerPosY,false))
                    return true;
            }
        }
        return false;
    }
    else
    {
        // check rectangular bounds only
        if (((testerPosX - objPosX) < this->getWidth() && (objPosX - testerPosX) < tester->getWidth()) &&
            ((testerPosY - objPosY) < this->getHeight() && (objPosY - testerPosY) < tester->getHeight())) return true;

        return false;
    }
}

Penjin::Directions CollisionRegion::directionTest(const CollisionRegion* const tester, CRbool fullShape) const
{
    // check for collision first
    if (not hitTest(tester,fullShape))
    {
        return diNONE;
    }
    // now check collision direction, by a simple check of the overlaping area
    else
    {
        // calculate overlaping pixels
        float diffX = min(this->getX() + this->getWidth(), tester->getX() + tester->getWidth()) - max(this->getX(), tester->getX());
        float diffY = min(this->getY() + this->getHeight(), tester->getY() + tester->getHeight()) - max(this->getY(), tester->getY());

        // check which side overlaps more (relatively)
        if (diffX / min(this->getWidth(),tester->getWidth()) > diffY / min(this->getHeight(),tester->getHeight()))
        {
            // more X -> top/bottom collision
            if ((this->getY() + this->getHeight()/2) > (tester->getY() + tester->getHeight()/2))
                return diTOP;
            else
                return diBOTTOM;
        }
        else
        {
            // more Y -> left/right collision
            if ((this->getX() + this->getWidth()/2) > (tester->getX() + tester->getWidth()/2))
                return diLEFT;
            else
                return diRIGHT;
        }
    }
}

Penjin::Directions CollisionRegion::directionTest(const CollisionRegion* const tester, const Vector2d<float>& posObj, const Vector2d<float>& posTester, CRbool fullShape) const
{
    // check for collision first
    if (not hitTest(tester,posObj,posTester,fullShape))
    {
        return diNONE;
    }
    // now check collision direction, by a simple check of the overlaping area
    else
    {
        float objPosX = posObj.x + this->getRegionOffsetX();
        float objPosY = posObj.y + this->getRegionOffsetY();
        float testerPosX = posTester.x + tester->getRegionOffsetX();
        float testerPosY = posTester.y + tester->getRegionOffsetY();

        // calculate overlaping pixels
        float diffX = min(objPosX + this->getWidth(), testerPosX + tester->getWidth()) - max(objPosX, testerPosX);
        float diffY = min(objPosY + this->getHeight(), testerPosY + tester->getHeight()) - max(objPosY, testerPosY);

        // check which side overlaps more (relatively)
        if (diffX / min(this->getWidth(),tester->getWidth()) > diffY / min(this->getHeight(),tester->getHeight()))
        {
            // more X -> top/bottom collision
            if ((objPosY + this->getHeight()/2) > (testerPosY + tester->getHeight()/2))
                return diTOP;
            else
                return diBOTTOM;
        }
        else
        {
            // more Y -> left/right collision
            if ((objPosX + this->getWidth()/2) > (testerPosX + tester->getWidth()/2))
                return diLEFT;
            else
                return diRIGHT;
        }
    }
}

void  CollisionRegion::render()
{
    if (map)
    {
        map->setPosition(pos);
        map->render();
    }
    if (not showRect && region.w != 0 && region.h != 0)
    {
        showRect = new Rectangle;
        showRect->setDimensions ( Vector2d<int>(region.w,region.h));
        showRect->setColour(Colour(GREEN));
        showRect->setDrawWidth(max(getWidth() / 100.0, 1.0));
    }
    if (showRect)
    {
        showRect->setDimensions(region.w,region.h);
        showRect->setPosition(pos.x + region.x,pos.y + region.y);
        showRect->render();
    }
}
