#include "AccelerationObject.h"
using Penjin::AccelerationObject;

AccelerationObject::AccelerationObject()
{
    //ctor
}

AccelerationObject::~AccelerationObject()
{
    //dtor
}

void AccelerationObject::update()
{
    velocity+=(acceleration+gravity);
    VelocityObject::update();
}

void AccelerationObject::setAccelerationX(const float& x)
{
    acceleration.x = x;
}

void AccelerationObject::setAccelerationY(const float& y)
{
    acceleration.y = y;
}

float AccelerationObject::getAccelerationX()
{
    return acceleration.x;
}

float AccelerationObject::getAccelerationY()
{
    return acceleration.y;
}

Vector2d<float> AccelerationObject::getAcceleration()const
{
    return acceleration;
}
