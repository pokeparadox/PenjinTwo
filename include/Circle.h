#ifndef CIRCLE_H
#define CIRCLE_H

#include "Primitive.h"
#include "RadialObject.h"

namespace Penjin
{
    class Circle : public Primitive, public RadialObject
    {
        public:
            Circle();
            virtual ~Circle();

            virtual void render();

        protected:
        private:
    };
}
#endif // CIRCLE_H
