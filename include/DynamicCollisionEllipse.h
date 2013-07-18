#ifndef DYNAMICCOLLISIONELLIPSE_H
#define DYNAMICCOLLISIONELLIPSE_H

#include "DynamicCollisionObject.h"

namespace Penjin
{
    class Ellipse;
    class DynamicCollisionEllipse : public DynamicCollisionObject
    {
        public:
            /** Default constructor */
            DynamicCollisionEllipse();
            /** Default destructor */
            virtual ~DynamicCollisionEllipse();

            virtual void render();
            virtual void queueRender();
            virtual void update();

            virtual bool hasCollided(CollisionObject* obj);
            virtual bool hasCollided(DynamicCollisionObject* obj);
            virtual bool hasCollided(DynamicCollisionEllipse* obj);

            void setColour(const Colour& c);
            void setDrawWidth(const int& w);

            Vector2d<float> getPosition(){DynamicCollisionObject::getPosition();}
            template <class T>
            void setPosition(const T& pos){DynamicCollisionObject::setPosition(pos);}

            template <class T>
            void setPosition(const T& x, const T& y){DynamicCollisionObject::setPosition(x,y);}

            virtual void setRadius(unsigned int r);
            virtual void setRadius2(unsigned int r2);
            virtual void setDiameter(unsigned int d);
            virtual void setDiameter2(unsigned int d2);

            virtual Vector2d<int> getCentrePoint();

        protected:
            Ellipse* ellipse;

        private:
    };
}


#endif // DYNAMICCOLLISIONELLIPSE_H
