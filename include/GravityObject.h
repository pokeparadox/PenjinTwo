#ifndef GRAVITYOBJECT_H
#define GRAVITYOBJECT_H

#include "VelocityObject.h"

namespace Penjin
{
    class GravityObject : public VelocityObject
    {
        public:
            /** Default constructor */
            GravityObject();
            /** Default destructor */
            virtual ~GravityObject();

            virtual void update();

            template <class T>
            void setGravity(const T& g){gravity.x=g.x;gravity.y=g.y;/*rescaleG();*/}

            template <class T>
            void setGravity(const T& x, const T& y){gravity.x=x;gravity.y=y;/*rescaleG();*/}

            void setGravityX(const float& x);
            void setGravityY(const float& y);
            float getGravityX();
            float getGravityY();

            Vector2d<float> getGravity()const;
            //Vector2d<float> getScaledGravity();
        protected:
            //void rescaleG();
            Vector2d<float> gravity;    //!< Member variable "gravity"
            //Vector2d<float> scaledG;    //!< Scaled value of gravity "scaledG"
    };
}
#endif // GRAVITYOBJECT_H
