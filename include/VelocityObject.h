#ifndef VELOCITYOBJECT_H
#define VELOCITYOBJECT_H

#include "PositionObject.h"
#include "UpdateObject.h"

namespace Penjin
{
    class VelocityObject : public PositionObject, public UpdateObject
    {
        public:
            /** Default constructor */
            VelocityObject();
            /** Default destructor */
            virtual ~VelocityObject();

            virtual void update();


            template <class T>
            void setVelocity(const T& v){velocity.x=v.x;velocity.y=v.y;/*rescaleV();*/}

            template <class T>
            void setVelocity(const T& x, const T& y){velocity.x=x;velocity.y=y;/*rescaleV();*/}

            void setVelocityX(const float& x);
            void setVelocityY(const float& y);
            float getVelocityX();
            float getVelocityY();

            Vector2d<float> getVelocity()const;
            //Vector2d<float> getScaledVelocity();

        protected:
            //void rescaleV();
            Vector2d<float> velocity; //!< Member variable "velocity"
            //Vector2d<float> scaledV;
    };

}
#endif // VELOCITYOBJECT_H
