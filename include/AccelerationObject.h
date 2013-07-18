#ifndef ACCELERATIONOBJECT_H
#define ACCELERATIONOBJECT_H

#include "GravityObject.h"

namespace Penjin
{
    class AccelerationObject : public GravityObject
    {
        public:
            /** Default constructor */
            AccelerationObject();
            /** Default destructor */
            virtual ~AccelerationObject();

            virtual void update();

            template <class T>
            void setAcceleration(const T& a){acceleration.x=a.x;acceleration.y=a.y;/*rescaleG();*/}

            template <class T>
            void setAcceleration(const T& x, const T& y){acceleration.x=x;acceleration.y=y;/*rescaleG();*/}

            void setAccelerationX(const float& x);
            void setAccelerationY(const float& y);
            float getAccelerationX();
            float getAccelerationY();

            Vector2d<float> getAcceleration()const;

        protected:
        private:
            Vector2d<float> acceleration; //!< Member variable "acceleration"
    };
}
#endif // ACCELERATIONOBJECT_H
