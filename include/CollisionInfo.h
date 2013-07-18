#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "Vector2d.h"
#include "SimpleDirection.h"
#include "Colour.h"

namespace Penjin
{
    struct CollisionInfo
    {
      Vector2d<float> collisionPosition;
      Vector2d<float> contactPoint;   //!< Member variable "contactPoint"
      bool hasCollided;               //!< Member variable "hasCollided"
      SimpleDirection direction;      //!< Member variable "direction"
      float angle;                    //!< Angle of collision
      long ticks;                     //!< No. of ticks when collision was tested
      Colour type;                    //!< Member variable "type"
    };
}
#endif // COLLISIONINFO_H
