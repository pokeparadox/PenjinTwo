#ifndef SCREENQUADTREE_H
#define SCREENQUADTREE_H


#include "Object.h"
#include "DoubleVector.h"
#include <vector>
using std::vector;
// This is a basic 2 tier quad tree stored in an array of 16 slots.

namespace Penjin
{
    class DynamicCollisionObject;
    class CollisionObject;
    class ScreenQuadTree : public Object
    {
        public:
            /** Default constructor */
            ScreenQuadTree();
            /** Default destructor */
            virtual ~ScreenQuadTree();

            //  Reset DYNAMIC objects.
            void clear();
            //  Reset all objects
            void clearAll();

            //  Add a obj to tree for processing,
            void push(CollisionObject* obj);


            bool hasCollidedObjects();
            //  Geta vector of all DynObjs that have collided.
            vector<DynamicCollisionObject*> getCollidedObjects();


        protected:
        private:
        enum QUADRANTS
            {
                TLTL=0,
                TLTR=1,
                TRTL=2,
                TRTR=3,
                TLBL=4,
                TLBR=5,
                TRBL=6,
                TRBR=7,
                BLTL=8,
                BLTR=9,
                BRTL=10,
                BRTR=11,
                BLBL=12,
                BLBR=13,
                BRBL=14,
                BRBR=15
            };
            void pushSort(CollisionObject* obj, QUADRANTS q);
            void pushSort(DynamicCollisionObject* obj, QUADRANTS q);

            enum CENTRES
            {
              CENTRE=0,
              TOPLEFT=1,
              TOPRIGHT=2,
              BOTLEFT=3,
              BOTRIGHT=4
            };
            Vector2d<float>    centres[5];        //  Centre of the screen for each level

            DoubleVector<CollisionObject*>    staticObjects;    //  All stationary objects.
            DoubleVector<DynamicCollisionObject*> dynObjects;  //  All Dyanmic objs

            vector<DynamicCollisionObject*> collidedObjects;    //  Stores objects that are known to have collided.
    };
}
#endif // SCREENQUADTREE_H
