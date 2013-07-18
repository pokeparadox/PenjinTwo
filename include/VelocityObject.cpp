#include "VelocityObject.h"
//#include "GFX.h"
using Penjin::VelocityObject;


VelocityObject::VelocityObject()
{
    //ctor
}

VelocityObject::~VelocityObject()
{
    //dtor
}

void VelocityObject::update()
{
    //  we update position based on velocity.
    position += velocity;
    rescale();
}

void VelocityObject::setVelocityX(const float& x)
{
    velocity.x = x;
    // If we are not scaling, then the scaled size is the same
    /*
    if(GFX->getScaleMode() == smNONE)
        scaledV.x = x;
    else
        scaledV.x =  (float)(velocity.x * GFX->getPixelScale().x) + 0.5f;*/
}

void VelocityObject::setVelocityY(const float& y)
{
    velocity.y = y;
     // If we are not scaling, then the scaled size is the same
    /*if(GFX->getScaleMode() == smNONE)
        scaledV.y = y;
    else
        scaledV.y =  (float)(velocity.y * GFX->getPixelScale().y) + 0.5f;*/
}

float VelocityObject::getVelocityX()
{
    return velocity.x;
}

float VelocityObject::getVelocityY()
{
    return velocity.y;
}

Vector2d<float> VelocityObject::getVelocity()const
{
    return velocity;
}

/*Vector2d<float> VelocityObject::geScaledVelocity()
{
    return scaledV;
}

void VelocityObject::rescaleV()
{
    if(GFX->getScaleMode() == smNONE)
        scaledV = velocity;
    else
        scaledV = velocity * GFX->getPixelScale();
}
*/
