#include "CollisionObject.h"
#include "CollisionInfo.h"
using Penjin::CollisionObject;
using Penjin::CollisionInfo;
#include "PhysicsProcessor.h"

CollisionObject::CollisionObject()
{
    //ctor
    lastCollision.hasCollided = false;
}

CollisionObject::~CollisionObject()
{
    //dtor
}

bool CollisionObject::hasCollided(CollisionObject* objB)
{
    PPU::getInstance()->collidedRectangleRectangle(position, dimensions,objB->getPosition(), objB->getDimensions());
    lastCollision = PPU::getInstance()->getLastCollisionA();
    objB->setLastCollision(PPU::getInstance()->getLastCollisionA());
    return lastCollision.hasCollided;
}

void CollisionObject::setLastCollision(CollisionInfo info)
{
   lastCollision = info;
}

CollisionInfo CollisionObject::getLastCollision()
{
   return lastCollision;
}
