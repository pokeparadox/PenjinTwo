#ifndef DYNAMICCOLLISIONOBJECT_H
#define DYNAMICCOLLISIONOBJECT_H

#include "AccelerationObject.h"
#include "CollisionObject.h"
namespace Penjin
{
    class DynamicCollisionObject : public CollisionObject
    {
        public:
            /** Default constructor */
            DynamicCollisionObject();
            /** Default destructor */
            virtual ~DynamicCollisionObject();

            virtual bool hasCollided(DynamicCollisionObject* obj);
            virtual bool hasCollided(CollisionObject* obj);

            vector<CollisionObject*> getCollided() {return collided;}
            void collidedWith(CollisionObject* obj);
            void clearCollided();


            template <class T>
            void setPosition(const T& pos){acceleration.setPosition(pos);CollisionObject::setPosition(pos);}
            template <class T>
            void setPosition(const T& x, const T& y){acceleration.setPosition(x,y);CollisionObject::setPosition(x,y);}
            virtual Vector2d<float> getPosition(){return acceleration.getPosition();}
            template <class T>
            void setVelocity(const T& v){acceleration.setVelocity(v);}
            template <class T>
            void setVelocityX(const T& x){acceleration.setVelocityX(x);}
            Vector2d<float> getVelocity(){return acceleration.getVelocity();}
            float getVelocityX(){return acceleration.getVelocityX();}
            virtual void setGravityY(const float&);

            template <class T>
            void setAcceleration(const T& a){acceleration.setAcceleration(a);}
            void setAccelerationX(const float& a){acceleration.setAccelerationX(a);}
            float getAccelerationX(){return acceleration.getAccelerationX();}
            //  We just render the rectangle.
            //virtual void render();
            virtual void update();
            void revert();

        protected:
            /// Objects which this one has collided with.
            vector<CollisionObject*> collided;
            AccelerationObject acceleration;
            PositionObject oldPosition;
        private:
    };
}
#endif // DYNAMICCOLLISIONOBJECT_H
