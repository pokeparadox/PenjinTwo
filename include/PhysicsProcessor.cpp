#include "PhysicsProcessor.h"
#include "Timer.h"
#include <iostream>
using Penjin::PhysicsProcessor;
using Penjin::Timer;
using std::cout;
using std::endl;


PhysicsProcessor::PhysicsProcessor() : timer(NULL)
{
    //ctor
    timer = new Timer;
    timer->setMode(MILLI_SECONDS);
}

PhysicsProcessor::~PhysicsProcessor()
{
    //dtor
    delete timer;
}


/// Point Collisions
// Check if a point is on a Line
bool PhysicsProcessor::collidedPointLine(Vector2d<float> point,Vector2d<float> lineStart, Vector2d<float> lineEnd)
{
    // Check if the point is actually lineStart or lineEnd
    if(point == lineStart or point == lineEnd)
    {
      /*  lastCollisionA.contactPoint = point;
        lastCollisionA.hasCollided = true;
        lastCollisionA.ticks = timer->getTicks();*/
        return true;
    }

    // Check if line is horizontal or vertical
    // Then we can make quick checks
    if(lineStart.x == lineEnd.x == point.x)
    {
        // Line vertical
        if(point.y >= lineStart.y and point.y <= lineEnd.y)
        {
            /*lastCollisionA.contactPoint = point;
            lastCollisionA.hasCollided = true;
            lastCollisionA.ticks = timer->getTicks();*/
            return true;
        }
    }
    else if(lineStart.y == lineEnd.y == point.y)
    {
        //  line horizontal
        if(point.x >= lineStart.x and point.x <= lineEnd.x)
        {
            /*lastCollisionA.contactPoint = point;
            lastCollisionA.hasCollided = true;
            lastCollisionA.ticks = timer->getTicks();*/
            return true;
        }
    }

    Vector2d<float> AB = lineEnd-lineStart;
    Vector2d<float> AC = point-lineStart;

    float magAB = AB.lengthSquared();
    float magAC = AC.lengthSquared();
    //  If one vector is greater in magnitude than the other, then point is not on the line.
    if(magAC > magAB)
    {
        /*lastCollisionA.contactPoint = point;
        lastCollisionA.hasCollided = false;
        lastCollisionA.ticks = timer->getTicks();*/
        return false;
    }

    //  Now take unit vectors and see if the directions match
    AB.normalise();
    AC.normalise();

    AB = AC - AB;

    //  Same direction so collision has occurred
    if(AB.lengthSquared() == 0)
    {
        /*lastCollisionA.contactPoint = point;
        lastCollisionA.hasCollided = true;
        lastCollisionA.ticks = timer->getTicks();*/
        return true;
    }

    /*lastCollisionA.contactPoint = point;
    lastCollisionA.hasCollided = false;
    lastCollisionA.ticks = timer->getTicks();*/
    return false;
}
bool PhysicsProcessor::collidedLineLine(Vector2d<float> p1, Vector2d<float> p2,Vector2d<float> lineStart, Vector2d<float> lineEnd)
{
    return false;
}

bool PhysicsProcessor::collidedPointVerticalLimit(Vector2d<float> point, float xPos, int direction)
{
    //  Left of this line limit
    if(direction<0)
    {
       return(point.x < xPos);
        /*lastCollisionA.hasCollided = (point.x < xPos);
        lastCollisionA.ticks = timer->getTicks();
        if(lastCollisionA.hasCollided)
        {
            lastCollisionA.contactPoint = point;
            //  Collided from the left
            lastCollisionA.direction = diLEFT;
        }
        return lastCollisionA.hasCollided;*/
    }
    //  Right of the line limit
    else if(direction>0)
    {
       return(point.x > xPos);
        /*lastCollisionA.hasCollided = (point.x > xPos);
        lastCollisionA.ticks = timer->getTicks();
        if(lastCollisionA.hasCollided)
        {
            lastCollisionA.contactPoint = point;
            //  Collided from the right
            lastCollisionA.direction = diRIGHT;
        }
        return lastCollisionA.hasCollided;*/
    }

    return (point.x == xPos);
    /*lastCollisionA.hasCollided = (point.x == xPos);
    lastCollisionA.ticks = timer->getTicks();
    if(lastCollisionA.hasCollided)
    {
        lastCollisionA.contactPoint = point;
        //  Collided point is on line.
        lastCollisionA.direction = diMIDDLE;
    }
    return lastCollisionA.hasCollided;*/
}

bool PhysicsProcessor::collidedPointHorizontalLimit(Vector2d<float> point, float yPos, int direction)
{
    //  Below of this line limit
    if(direction<0)
    {
       return (point.y < yPos);
        /*lastCollisionA.hasCollided = (point.y < yPos);
        lastCollisionA.ticks = timer->getTicks();
        if(lastCollisionA.hasCollided)
        {
            lastCollisionA.contactPoint = point;
            //  Collided from the bottom
            lastCollisionA.direction = diBOTTOM;
        }
        return lastCollisionA.hasCollided;
        */
    }

    //  Above of the line limit
    else if(direction>0)
    {
       return (point.y > yPos);
        /*lastCollisionA.hasCollided = (point.y > yPos);
        lastCollisionA.ticks = timer->getTicks();
        if(lastCollisionA.hasCollided)
        {
            lastCollisionA.contactPoint = point;
            //  Collided from the top
            lastCollisionA.direction = diTOP;
        }
        return lastCollisionA.hasCollided;*/
    }

    return (point.y == yPos);
    /*lastCollisionA.hasCollided = (point.y == yPos);
    lastCollisionA.ticks = timer->getTicks();
    if(lastCollisionA.hasCollided)
    {
        lastCollisionA.contactPoint = point;
        //  Point is on the line.
        lastCollisionA.direction = diMIDDLE;
    }
    return lastCollisionA.hasCollided;*/
}

bool PhysicsProcessor::collidedPointRectangle(Vector2d<float> point,Vector2d<float> position, Vector2d<float> dimensions)
{
    return false;
}

bool PhysicsProcessor::collidedLineRectangle(Vector2d<float> p1, Vector2d<float> p2,Vector2d<float> position, Vector2d<float> dimensions)
{
    if(p1 == p2)
        return collidedPointRectangle(p1, position,dimensions);
    if(dimensions.x == 0 || dimensions.y == 0)
        return collidedLineLine(p1,p2,position, position + dimensions);
    //  TODO Line to Rectangle test
    return false;
}

/// Rectangle Collisions
bool PhysicsProcessor::collidedRectangleRectangle(Vector2d<float> pos1, Vector2d<float> dim1,Vector2d<float> pos2, Vector2d<float> dim2)
{
        // check rectangular bounds only
        if (pos1.x + dim1.x < pos2.x ||
         pos1.x > pos2.x + dim2.x ||
         pos1.y > pos2.y + dim2.y ||
         pos1.y + dim1.y < pos2.y)
        {
            /*lastCollisionA.hasCollided = true;
            lastCollisionA.ticks = timer->getTicks();
            lastCollisionB.hasCollided = true;
            lastCollisionB.ticks = timer->getTicks();*/

            //i.direction = this->directionTest(tester,fullShape);
            return false;
        }
        cout << "BONG" << endl;
        //return lastCollisionA.hasCollided;
        return true;
}

/// Circle Collisions
bool PhysicsProcessor::collidedCircleCircle(Vector2d<float> pos1, float r1,Vector2d<float> pos2, float r2)
{
       //  If the bounding boxes don't collide then the circle can't collide.
    /*lastCollisionA.ticks = timer->getTicks();
    lastCollisionA.hasCollided = false;
    lastCollisionB.ticks = lastCollisionA.ticks;
    lastCollisionB.hasCollided = false;*/
    //  1st we create bounding boxes for each circle and do a Rectangle test
    if(collidedRectangleRectangle(pos1, Vector2d<float> (2*r1,2*r1),pos2, Vector2d<float>(2*r2,2*r2)))
    {
        //  If the boxes overlap do a radial distance check
        Vector2d<float> diff = pos2 - pos1;
        if(diff.lengthSquared() <= (r1*r1) + (r2*r2))
        {
            //lastCollisionA.hasCollided = true;
            //lastCollisionB.hasCollided = true;
            return true;
        }
    }
    return false;
}

bool PhysicsProcessor::collidedCircleCircleDirection(Vector2d<float> pos1, float r1,Vector2d<float> pos2, float r2)
{
    //  We check if the circle has collided
    if(collidedCircleCircle(pos1,r1,pos2,r2))
    {
        //  If it has we do further calculations
        Vector2d<float> diff = pos2-pos1;
        Vector2d<float> cp = diff;
        cp.normalise();
        //lastCollisionA.contactPoint = pos1 + (cp * r1);
        //lastCollisionA.ticks = timer->getTicks();

        //  If it has we do further calculations
        diff = pos1 - pos2;
        cp = diff;
        cp.normalise();
        //lastCollisionB.contactPoint = pos2 + (cp * r2);
        //lastCollisionB.ticks = lastCollisionA.ticks;
        return true;
    }
    //return lastCollisionA.hasCollided;
    return false;
}

//  Ellipse Collisions
bool PhysicsProcessor::collidedRectangleEllipse(Vector2d<float> pos1, Vector2d<float> dims,Vector2d<float> pos2, float r1, float r2)
{
       //  If the bounding boxes don't collide then the circle can't collide.
  /*  lastCollisionA.ticks = timer->getTicks();
    lastCollisionA.hasCollided = false;
    lastCollisionB.ticks = lastCollisionA.ticks;
    lastCollisionB.hasCollided = false;*/
        //  1st we create bounding boxes for the circle and do a Rectangle test against the Rectangle.
    if(collidedRectangleRectangle(pos1, dims,pos2, Vector2d<float>(2*r1,2*r2)))
    {
        //  Check the tallest extremites
        if(collidedLineRectangle(pos2 - Vector2d<float>(0.0f,r2),pos2 + Vector2d<float>(0.0f,r2),pos1,dims )
           || collidedLineRectangle(pos2 - Vector2d<float>(r1,0.0f),pos2 + Vector2d<float>(r1,0.0f),pos1,dims)
           )
            return true;
        /// NOTE we are cheating the result for now.
        float meanR = r1 + r2 * 0.5f;

        //  If the boxes overlap do a radial distance check
        Vector2d<float> diff = pos2 - pos1;
        float meanDim = dims.x + dims.y * 0.5f;
        if(diff.lengthSquared() <= (meanDim*meanDim) + (r2*r2))
        {
            //lastCollision.hasCollided = true;
            return true;
        }
        //return true;
    }
    return false;
}
/*
void PhysicsProcessor::resetLastCollisionA()
{
    lastCollisionA.hasCollided = false;
    lastCollisionA.ticks = 0;
    lastCollisionA.contactPoint = Vector2d<float>(0,0);
    lastCollisionA.direction = diNONE;
    lastCollisionA.angle = 0;
    lastCollisionA.type = Colour(MAGENTA);
}

void PhysicsProcessor::resetLastCollisionB()
{
   lastCollisionB.hasCollided = false;
    lastCollisionB.ticks = 0;
    lastCollisionB.contactPoint = Vector2d<float>(0,0);
    lastCollisionB.direction = diNONE;
    lastCollisionB.angle = 0;
    lastCollisionB.type = Colour(MAGENTA);
}
*/
