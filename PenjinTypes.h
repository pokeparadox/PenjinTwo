/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef TYPES_H
#define TYPES_H
/*
NOTE: Be very careful with inclusion as the typedefs will affect any headers included afterwards!
*/

#include <string>

//  TYPE SHORTHANDS
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

//  VECTORS - Have length() operations and such
#include "trenki/vector_math.h"
#include "trenki/fixed_class.h"
/*#include "Vector2df.h"
class Vector2dx;
#include "Vector2di.h"
#include "Vector3df.h"
class Vector3dx;//#include "Vector3dx.h"
#include "Vector3di.h"*/
typedef vmath::vec4<int> Vector4di;                             //  int 4d vector
typedef vmath::vec4<float> Vector4df;                           //  float 4d vector
typedef vmath::vec4<fixedpoint::fixed_point<16> > Vector4dx;    //  Fixed point 4d vector

typedef fixedpoint::fixed_point<16> Fixed;                      //  Default fixed point

//  POINTS - simple spatial points
struct Point2df{float x;float y;};
struct Point2dx{Fixed x;Fixed y;};
struct Point2di{int x;int y;};
struct Point3df{float x;float y;float z;};
struct Point3dx{Fixed x;Fixed y;Fixed z;};
struct Point3di{int x;int y;int z;};
struct Point4df{float x;float y;float z;float w;};
struct Point4dx{Fixed x;Fixed y;Fixed z;Fixed w;};
struct Point4di{int x;int y;int z;int w;};

//  Model Vectors
typedef float ModelVector3f[3];
typedef float ModelVector2f[2];
typedef Fixed ModelVector3x[3];
typedef Fixed ModelVector2x[2];
typedef int ModelVector3i[3];
typedef int ModelVector2i[2];
// CONSTANT REFERENCES
typedef const bool& CRbool;
typedef const int& CRint;
typedef const unsigned int& CRuint;
typedef const short& CRshort;
typedef const unsigned short& CRushort;
typedef const char& CRchar;
typedef const unsigned char& CRuchar;
typedef const long& CRlong;
typedef const unsigned long& CRulong;
typedef const float& CRfloat;
typedef const double& CRdouble;
typedef const Fixed& CRFixed;
typedef const std::string& CRstring;

//  #undef as necessary
#ifdef PENJIN_FIXED
    /// Forced float types
    typedef float FLOAT;
    typedef const float& CRFLOAT;
    typedef Vector2df VECTOR2DF;
    typedef Vector3df VECTOR3DF;
    typedef Vector4df VECTOR4DF;
    typedef Point2df POINT2DF;
    typedef Point3df POINT3DF;
    typedef Point4df POINT4DF;
    /// float to Fixed conversion
    #define Vector2df Vector2dx
    #define Vector3df Vector3dx
    #define Vector4df Vector4dx
    #define Point2df Point2dx
    #define Point3df Point3dx
    #define Point4df Point4dx
    #define float Fixed
    #define CRfloat CRFixed
#endif  //  PENJIN_FIXED

// Vertex helpers
#ifdef PENJIN_3D
    struct ColourVertex
    {
        Point3df vertex;
        Point4df colour;
    };
#else
    #ifdef PENJIN_SDL
        struct ColourVertex
        {
            Point2di vertex;
            Point4di colour;
        };
    #else
        struct ColourVertex
        {
            Point2df vertex;
            Point4df colour;
        };
    #endif
#endif

//#include "Variable.h"	        // multiple type storage
#endif	//	TYPES_H
