#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

#include "Rectangle.h"
#include "CollisionInfo.h"

// CollisionObject is something a DynamicCollisionObject can potentially crash into.
// It is intended to be stationary.
// It can check against other CollisionObjects for if want to do some manual routines.

namespace Penjin
{
    class CollisionObject : public Rectangle
    {
        public:
            CollisionObject();
            virtual ~CollisionObject();
            //virtual void render()=0;

            //  CollisionObject and CollisionObject always false  as no shape info.

            // We use this function to check if a collision has occured
            virtual bool hasCollided(CollisionObject* obj);

            void setLastCollision(CollisionInfo info);

            //  We can get any details about the collision from this function.
            CollisionInfo getLastCollision();

            virtual Vector2d<int> getCentrePoint()
            {
                return position  + (dimensions * 0.5f);
            }

        protected:
            CollisionInfo lastCollision;
    };
}
#endif // COLLISIONOBJECT_H
