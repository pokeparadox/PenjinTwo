#include "Circle.h"
using Penjin::Circle;

Circle::Circle()
{
    //ctor
}

Circle::~Circle()
{
    //dtor
}

void Circle::render()
{
    GFX->setDrawColour(*this);
    GFX->drawCircle(position,getRadius());
}
