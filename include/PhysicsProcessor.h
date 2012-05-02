#ifndef PHYSICSPROCESSOR_H
#define PHYSICSPROCESSOR_H

#include "Singleton.h"
#include "PenjinTypes.h"
namespace Penjin
{
    class PhysicsProcessor
    {
        public:
            PhysicsProcessor();
            virtual ~PhysicsProcessor();


            /// Point Collisions
            // Check if a collision occurred between two points
            bool collidedPointPoint(Vector2d<float> a,Vector2d<float> b){return (a == b);}
            // Check if a point is on a Line
            bool collidedPointLine(Vector2d<float> point,Vector2d<float> lineStart, Vector2d<float> lineEnd);
            // Check if a point is inside a rectangle
            bool collidedPointRectangle(Vector2d<float> point,Vector2d<float> position, Vector2d<float> dimensions);
            // Check if a point is inside a circle
            bool collidedPointCircle(Vector2d<float> point,Vector2d<float> position, float radius);
            // Check if a point is inside an ellipse
            bool collidedPointEllipse(Vector2d<float> point, Vector2d<float> position, float r1, float r2);
            // Check if a point is passed a vertical limit
            //  direction is pos or neg 1. If neg we are checking if point is passed over to left of vertical line
            // positive value is to the right of this line
            bool collidedPointVerticalLimit(Vector2d<float> point, float xPos, int direction);
            // Check if a point is passed a horizontal limit
            //  direction is pos or neg 1. If neg we are checking if point is passed over to below of horizontal line
            // positive value is above of this line
            bool collidedPointHorizontalLimit(Vector2d<float> point, float xPos, int direction);

            /// Line Collisions
            // Check if a Line is on a Line
            bool collidedLineLine(Vector2d<float> p1, Vector2d<float> p2,Vector2d<float> lineStart, Vector2d<float> lineEnd);
            // Check if a Line is inside a rectangle
            bool collidedLineRectangle(Vector2d<float> p1, Vector2d<float> p2,Vector2d<float> position, Vector2d<float> dimensions);
            // Check if a Line is inside a circle
            bool collidedLineCircle(Vector2d<float> p1, Vector2d<float> p2,Vector2d<float> position, float radius);
            // Check a Line crosses an Ellipse
            bool collidedLineEllipse(Vector2d<float> p1, Vector2d<float> p2, Vector2d<float> position, float r1, float r2);

            /// Rectanle Collisions
            bool collidedRectangleRectangle(Vector2d<float> pos1, Vector2d<float> dim1,Vector2d<float> pos2, Vector2d<float> dim2);
            bool collidedRectangleCircle(Vector2d<float> pos1, Vector2d<float> dims,Vector2d<float> pos2, float radius);
            bool collidedRectangleEllipse(Vector2d<float> pos1, Vector2d<float> dims,Vector2d<float> pos2, float r1, float r2);

            /// Circle Collisions
            bool collidedCircleCircle(Vector2d<float> pos1, float r1,Vector2d<float> pos2, float r2);
            bool collidedCircleEllipse(Vector2d<float> pos1, float r1,Vector2d<float> pos2, float r2a, float r2b);

            /// Ellipse Collisions
            bool collidedEllipseEllipse(Vector2d<float> pos1, float r1a, float r1b,Vector2d<float> pos2, float r2a, float r2b);

            //
            // Give the coords on object A where the collision occurred -1 -1 returnon no collision.
            //Vector2d <float> collided(a , b);

        protected:
        private:
    };
    typedef Singleton<PhysicsProcessor> PPU;
}

#endif // PHYSICSPROCESSOR_H
