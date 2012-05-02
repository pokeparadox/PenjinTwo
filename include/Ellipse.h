#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Primitive.h"
#include "RadialObject.h"

namespace Penjin
{
    class Ellipse : public Primitive, public RadialObject
    {
        public:
            Ellipse();
            virtual ~Ellipse();

            virtual void render();

        protected:
        private:
    };
}


#endif // ELLIPSE_H
