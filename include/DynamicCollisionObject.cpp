#include "DynamicCollisionObject.h"
#include "PhysicsProcessor.h"

#if _DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif // _DEBUG
using Penjin::DynamicCollisionObject;


DynamicCollisionObject::DynamicCollisionObject()
{
    //ctor
}

DynamicCollisionObject::~DynamicCollisionObject()
{
    //dtor
}

bool DynamicCollisionObject::hasCollided(CollisionObject* objB)
{
   //CollisionInfo oldInfo = lastCollision;
   //lastCollision.hasCollided = false;
   return PPU::getInstance()->collidedRectangleRectangle(Rectangle::getPosition(), dimensions,objB->getPosition(), objB->getDimensions());

    //lastCollision = PPU::getInstance()->getLastCollisionA();
    //objB->setLastCollision(PPU::getInstance()->getLastCollisionB());

    //  We keep a record that we collided if needed.
    //if(lastCollision.hasCollided)
    //{
      //  collidedWith(objB);
    //}
    //else
      //lastCollision = oldInfo;

    //return lastCollision.hasCollided;
}

bool DynamicCollisionObject::hasCollided(DynamicCollisionObject* objB)
{
   //CollisionInfo oldInfo = lastCollision;
   return PPU::getInstance()->collidedRectangleRectangle(Rectangle::getPosition(), dimensions,objB->Rectangle::getPosition(), objB->getDimensions());
    //lastCollision = PPU::getInstance()->getLastCollisionA();
    //objB->setLastCollision(PPU::getInstance()->getLastCollisionB());

    //  We keep a record that we collided if needed.
    //if(lastCollision.hasCollided)
    //{
      //  collidedWith(objB);
        //objB->collidedWith(this);
    //}
    //else
      //lastCollision = oldInfo;

    //return lastCollision.hasCollided;
}

void DynamicCollisionObject::collidedWith(CollisionObject* obj)
{
    collided.push_back(obj);
}

void DynamicCollisionObject::clearCollided()
{
    collided.clear();
}

void DynamicCollisionObject::update()
{
   clearCollided();
   // presume no collison at beginning of update
   lastCollision.hasCollided = false;
   oldPosition.setPosition(Rectangle::getPosition());
    // Updates accel, gravity, velocity and position.
    acceleration.update();

    // Do collision checks for rectangle.

    //  Update Rectangle (in CollisionObject)for drawing.
    CollisionObject::setPosition(acceleration.getPosition());
}

void DynamicCollisionObject::revert()
{
   setPosition(oldPosition.getPosition());
}

void DynamicCollisionObject::setGravityY(const float& g)
{
   acceleration.setGravityY(g);
}
