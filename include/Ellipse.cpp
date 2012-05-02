#include "Ellipse.h"
#include "GFX.h"
using Penjin::Ellipse;

Ellipse::Ellipse()
{
    //ctor
}

Ellipse::~Ellipse()
{
    //dtor
}

void Ellipse::render()
{
    GFX->setDrawColour(*this);
    GFX->drawEllipse(position,getRadius(),getRadius2());
}
