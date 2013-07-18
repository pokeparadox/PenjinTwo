#include "DynamicCollisionEllipse.h"
#include "PhysicsProcessor.h"
#include "Ellipse.h"
#include <iostream>
using Penjin::DynamicCollisionEllipse;
using Penjin::Ellipse;
using namespace std;
DynamicCollisionEllipse::DynamicCollisionEllipse()
{
    //ctor
    #ifdef _DEBUG
    Rectangle::setColour(MAGENTA);
    Rectangle::setDrawWidth(1);
    #endif
    ellipse = NULL;
    ellipse = new Ellipse();
}

DynamicCollisionEllipse::~DynamicCollisionEllipse()
{
    //dtor
    delete ellipse;
}


void DynamicCollisionEllipse::render()
{
    #ifdef _DEBUG
    Rectangle::render();
    #endif
    ellipse->setPosition(DynamicCollisionObject::getPosition() + Vector2d<float>(ellipse->getRadii()));
    ellipse->render();
}

Vector2d<int> DynamicCollisionEllipse::getCentrePoint()
{
    return ellipse->getPosition();
}

void DynamicCollisionEllipse::queueRender()
{
    #ifdef _DEBUG
    Rectangle::queueRender();
    #endif
    ellipse->setPosition(DynamicCollisionObject::getPosition() + Vector2d<float>(ellipse->getRadii()));
    ellipse->queueRender();
}

void DynamicCollisionEllipse::setColour(const Colour& c)
{
    ellipse->setColour(c);
}

void DynamicCollisionEllipse::setDrawWidth(const int& w)
{
    ellipse->setDrawWidth(w);
}

void DynamicCollisionEllipse::setRadius(unsigned int r)
{
    #ifdef _DEBUG
    Rectangle::setWidth(r*2);
    #endif
    ellipse->setRadius(r);
}

void DynamicCollisionEllipse::setRadius2(unsigned int r2)
{
    #ifdef _DEBUG
    Rectangle::setHeight(r2*2);
    #endif
    ellipse->setRadius2(r2);
}

void DynamicCollisionEllipse::setDiameter(unsigned int d)
{
    #ifdef _DEBUG
    Rectangle::setWidth(d);
    #endif
    ellipse->setDiameter(d);
}

void DynamicCollisionEllipse::setDiameter2(unsigned int d2)
{
    #ifdef _DEBUG
    Rectangle::setHeight(d2);
    #endif
    ellipse->setDiameter2(d2);
}

bool DynamicCollisionEllipse::hasCollided(CollisionObject* objB)
{
    //PPU::getInstance()->collidedRectangleRectangle(position, dimensions,objB->getPosition(), objB->getDimensions());
    //Vector2d<float> pos1, Vector2d<float> dims,Vector2d<float> pos2, float r1, float r2);
    return PPU::getInstance()->collidedRectangleEllipse(objB->getPosition(),objB->getDimensions(), acceleration.getPosition(), ellipse->getRadius(), ellipse->getRadius2());
    /*lastCollision = PPU::getInstance()->getLastCollisionA();
    objB->setLastCollision(PPU::getInstance()->getLastCollisionB());

    //  We keep a record that we collided if needed.
    if(lastCollision.hasCollided)
    {
        collidedWith(objB);
    }

    return lastCollision.hasCollided;*/
}

bool DynamicCollisionEllipse::hasCollided(DynamicCollisionObject* objB)
{
    return PPU::getInstance()->collidedRectangleEllipse(objB->getPosition(),objB->getDimensions(), acceleration.getPosition(), ellipse->getRadius(), ellipse->getRadius2());
    //PPU::getInstance()->collidedRectangleRectangle(position, dimensions,objB->getPosition(), objB->getDimensions());
    /*lastCollision = PPU::getInstance()->getLastCollisionA();
    objB->setLastCollision(PPU::getInstance()->getLastCollisionB());

    //  We keep a record that we collided if needed.
    if(lastCollision.hasCollided)
    {
        collidedWith(objB);
        objB->collidedWith(this);
    }

    return lastCollision.hasCollided;
    */
}

bool DynamicCollisionEllipse::hasCollided(DynamicCollisionEllipse* objB)
{
    //PPU::getInstance()->collidedRectangleRectangle(position, dimensions,objB->getPosition(), objB->getDimensions());

    lastCollision = PPU::getInstance()->getLastCollisionA();
    objB->setLastCollision(PPU::getInstance()->getLastCollisionB());

    //  We keep a record that we collided if needed.
    if(lastCollision.hasCollided)
    {
        collidedWith(objB);
        objB->collidedWith(this);
    }

    return lastCollision.hasCollided;
}

void DynamicCollisionEllipse::update()
{
    // Do Rectangle checks and update Rectangle.
    #ifdef _DEBUG
    Rectangle::setDimensions(ellipse->getDimensions());
    #endif
    DynamicCollisionObject::update();

    // Do Ellipse Checks

    // Update Ellipse  for Drawing
    //ellipse->setPosition(DynamicCollisionObject::getPosition() + ellipse->getDimensions() *0.5f);
    //ellipse->setDimensions(Rectangle::getDimensions());
}
