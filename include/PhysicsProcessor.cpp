#include "PhysicsProcessor.h"

using Penjin::PhysicsProcessor;

PhysicsProcessor::PhysicsProcessor()
{
    //ctor
}

PhysicsProcessor::~PhysicsProcessor()
{
    //dtor
}

// Check if a point is on a Line
bool PhysicsProcessor::collidedPointLine(Vector2d<float> point,Vector2d<float> lineStart, Vector2d<float> lineEnd)
{
    // Check if the point is actually lineStart or lineEnd
    if(point == lineStart or point == lineEnd)
        return true;

    // Check if line is horizontal or vertical
    // Then we can make quick checks
    if(lineStart.x == lineEnd.x == point.x)
    {
        // Line vertical
        if(point.y >= lineStart.y and point.y <= lineEnd.y)
            return true;
    }
    else if(lineStart.y == lineEnd.y == point.y)
    {
        //  line horizontal
        if(point.x >= lineStart.x and point.y <= lineEnd.x)
            return true;
    }

    Vector2d<float> AB = lineEnd-lineStart;
    Vector2d<float> AC = point-lineStart;

    float magAB = AB.lengthSquared();
    float magAC = AC.lengthSquared();
    //  If one vector is greater in magnitude than the other, then point is not on the line.
    if(magAC > magAB)
        return false;

    //  Now take unit vectors and see if the directions match
    AB.normalise();
    AC.normalise();

    AB = AC - AB;

    //  Same direction so collision has occurred
    if(AB.lengthSquared() == 0)
        return true;

    return false;
}


bool PhysicsProcessor::collidedPointVerticalLimit(Vector2d<float> point, float xPos, int direction)
{
    //  Left of this line limit
    if(direction<0)
        return(point.x < xPos);
    //  Right of the line limit
    else if(direction>0)
        return(point.x > xPos);

    return (point.x == xPos);
}

bool PhysicsProcessor::collidedPointHorizontalLimit(Vector2d<float> point, float yPos, int direction)
{
    //  Left of this line limit
    if(direction<0)
        return(point.y < yPos);
    //  Right of the line limit
    else if(direction>0)
        return(point.y > yPos);

    return (point.y == yPos);
}


