#include "GravityObject.h"
using Penjin::GravityObject;

GravityObject::GravityObject()
{
    //ctor
}

GravityObject::~GravityObject()
{
    //dtor
}

void GravityObject::update()
{
    velocity+=gravity;
    VelocityObject::update();
}

void GravityObject::setGravityX(const float& x)
{
    gravity.x = x;
}

void GravityObject::setGravityY(const float& y)
{
    gravity.y = y;
}

float GravityObject::getGravityX()
{
    return gravity.x;
}

float GravityObject::getGravityY()
{
    return gravity.y;
}

Vector2d<float> GravityObject::getGravity()const
{
    return gravity;
}

