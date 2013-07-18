#include "ScreenQuadTree.h"
#include "GFX.h"
#include "CollisionObject.h"
#include "DynamicCollisionObject.h"
using Penjin::ScreenQuadTree;
using Penjin::CollisionObject;
using Penjin::DynamicCollisionObject;

ScreenQuadTree::ScreenQuadTree()
{
    //ctor
    //  Set centre points
    centres[CENTRE] = GFX->getResolution() / 2;
    centres[TOPLEFT] = centres[CENTRE] / 2;
    centres[BOTRIGHT] = centres[TOPLEFT] * 3;

    centres[TOPRIGHT].x = centres[BOTRIGHT].x;
    centres[TOPRIGHT].y = centres[TOPLEFT].y;

    centres[BOTLEFT].x = centres[TOPLEFT].x;
    centres[BOTLEFT].y = centres[BOTRIGHT].y;

    staticObjects.resize(16);
    dynObjects.resize(16);
}

ScreenQuadTree::~ScreenQuadTree()
{
    //dtor
}

bool ScreenQuadTree::hasCollidedObjects()
{

    bool collided = false;
    //  Firstly STATIC objects are static and don't need to be tested against each other.
    //  DynamicObjects can collide with each other OR static objects.

    //  We check through each quadrant (or hextant since we are a 2 layer quadtree...)
    for(int i = 0; i < 16;++i)
    {
        //  We can only have a potential collision if there are some DynObjs in that quad
        size_t s = dynObjects.at(i).size();
        //  So we run through each DynObj
        for(int j = 0; j < s; ++j)
        {
            //  Start index 1 to avouid self comparison
            DynamicCollisionObject* objA = dynObjects.at(i,j);
            for(int k = 1;k < s; ++ k)
            {
                //  We also do this check to avoid self comparisions.
                if(j == k)
                    continue;

                //  And do the collision check
                if(objA->hasCollided(dynObjects.at(i,k)))
                {
                    collidedObjects.push_back(objA);
                    collided = true;
                }

            }

           //   After comparing we check to any static objs...

           //   Any dynObjs that have collided we add to a vector.
        }
    }
    return collided;
}

vector<DynamicCollisionObject*> ScreenQuadTree::getCollidedObjects()
{
    return collidedObjects;
}

void ScreenQuadTree::clear()
{
    dynObjects.clear();
}

void ScreenQuadTree::clearAll()
{
    dynObjects.clear();
    staticObjects.clear();
}

void ScreenQuadTree::push(CollisionObject* obj)
{
    // If we have an object
    if(obj != NULL)
    {
        //  Check for which quarter of the screen
        // TOP or bottom
        if(obj->getY() < centres[CENTRE].getY())
        {
            /// TOP
            if(obj->getX() < centres[CENTRE].getX())
            {
                ///TOPLEFT
                ////////////////////////
                //  Check for which quarter of the quadrant
                // TOP or bottom
                if(obj->getY() < centres[TOPLEFT].getY())
                {
                    /// TOP
                    if(obj->getX() < centres[TOPLEFT].getX())
                    {
                        ///TOPLEFT
                        ///TLTL
                        pushSort(obj,TLTL);
                    }
                    else
                    {
                        ///TOPRIGHT
                        ///TLTR
                        pushSort(obj,TLTR);
                    }
                }
                else
                {
                    ///BOTTOM
                    if(obj->getX() < centres[TOPLEFT].getX())
                    {
                        ///BOTLEFT
                        ///TLBL
                        pushSort(obj,TLBL);
                    }
                    else
                    {
                        ///BOTRIGHT
                        ///TLBR
                        pushSort(obj,TLBR);
                    }
                }
                //////////////////////
            }
            else
            {
                ///TOPRIGHT
                ////////////////////////
                //  Check for which quarter of the quadrant
                // TOP or bottom
                if(obj->getY() < centres[TOPRIGHT].getY())
                {
                    /// TOP
                    if(obj->getX() < centres[TOPRIGHT].getX())
                    {
                        ///TOPLEFT
                        ///TRTL
                        pushSort(obj,TRTL);
                    }
                    else
                    {
                        ///TOPRIGHT
                        ///TRTR
                        pushSort(obj,TRTR);
                    }
                }
                else
                {
                    ///BOTTOM
                    if(obj->getX() < centres[TOPRIGHT].getX())
                    {
                        ///BOTLEFT
                        ///TRBL
                        pushSort(obj,TRBL);
                    }
                    else
                    {
                        ///BOTRIGHT
                        ///TRBR
                        pushSort(obj,TRTR);
                    }
                }
                //////////////////////
            }
        }
        else
        {
            ///BOTTOM
            if(obj->getX() < centres[CENTRE].getX())
            {
                ///BOTLEFT
                ////////////////////////
                //  Check for which quarter of the quadrant
                // TOP or bottom
                if(obj->getY() < centres[BOTLEFT].getY())
                {
                    /// TOP
                    if(obj->getX() < centres[BOTLEFT].getX())
                    {
                        ///TOPLEFT
                        ///BLTL
                        pushSort(obj,BLTL);
                    }
                    else
                    {
                        ///TOPRIGHT
                        ///BLTR
                        pushSort(obj,BLTR);
                    }
                }
                else
                {
                    ///BOTTOM
                    if(obj->getX() < centres[BOTLEFT].getX())
                    {
                        ///BOTLEFT
                        ///BLBL
                        pushSort(obj,BLBL);
                    }
                    else
                    {
                        ///BOTRIGHT
                        ///BLBR
                        pushSort(obj,BLBR);
                    }
                }
                //////////////////////
            }
            else
            {
                ///BOTRIGHT
                ////////////////////////
                //  Check for which quarter of the quadrant
                // TOP or bottom
                if(obj->getY() < centres[BOTRIGHT].getY())
                {
                    /// TOP
                    if(obj->getX() < centres[BOTRIGHT].getX())
                    {
                        ///TOPLEFT
                        ///BRTL
                        pushSort(obj,BRTL);

                    }
                    else
                    {
                        ///TOPRIGHT
                        ///BRTR
                        pushSort(obj,BRTR);
                    }
                }
                else
                {
                    ///BOTTOM
                    if(obj->getX() < centres[BOTRIGHT].getX())
                    {
                        ///BOTLEFT
                        ///BRBL
                        pushSort(obj,BRBL);
                    }
                    else
                    {
                        ///BOTRIGHT
                        ///BRBR
                        pushSort(obj,BRBR);
                    }
                }
                //////////////////////
            }
        }
    }
}

void ScreenQuadTree::pushSort(CollisionObject* obj, QUADRANTS q)
{
    staticObjects.at(q).push_back(obj);
}

void ScreenQuadTree::pushSort(DynamicCollisionObject* obj, QUADRANTS q)
{
    dynObjects.at(q).push_back(obj);
}

