#ifndef VERTEXBASIC2D_H_INCLUDED
#define VERTEXBASIC2D_H_INCLUDED

/**
	\section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013 Kevin Winfield-Pantoja

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
/***************************************************************************************************
*   \file CLASS_NAME is INSERT DESCRIPTION
*   \author Kevin Winfield-Pantoja
*/


// This is the vertex shader which is executed for each individial vertex that
// needs to ne processed.

//  16 bit shader
struct VertexBasic2d_RGB {

	// This specifies that this shader is only going to use 1 vertex attribute
	// array. There you be used up to Renderer::MAX_ATTRIBUTES arrays.
	static const unsigned attribute_count = 1;

	// This specifies the number of varyings the shader will output. This is
	// for instance used when clipping.
	static const unsigned varying_count = 3;

	// This static function is called for each vertex to be processed.
	// "in" is an array of void* pointers with the location of the individial
	// vertex attributes. The "out" structure has to be written to.
	static void shade(const GeometryProcessor::VertexInput in, GeometryProcessor::VertexOutput &out)
	{
		// cast the first attribute array to the input vertex type
		const SoftwareColourVertex2d &v = *static_cast<const SoftwareColourVertex2d*>(in[0]);

		// x, y, z and w are the components that must be written by the vertex
		// shader. They all have to be specified in 16.16 fixed point format.
		out.x = static_cast<int>((v.vertex.x * (1 << 16)));
		out.y = static_cast<int>((v.vertex.y * (1 << 16)));
		out.z = 0;
		out.w = 1 << 16;

		// The vertexoutput can have up to Rasterizer::MAX_VARYING varying
		// parameters. These are just integer values which will be interpolated
		// across the primitives. The higher bits of these integers will be
		// interpolated more precicely so the values [0, 255] are shifted left.
		out.varyings[0] = v.colour.x << 16;
		out.varyings[1] = v.colour.y << 16;
		out.varyings[2] = v.colour.z << 16;
	}
};

//  16 bit shader
struct VertexBasic2d_RGBA {

	// This specifies that this shader is only going to use 1 vertex attribute
	// array. There you be used up to Renderer::MAX_ATTRIBUTES arrays.
	static const unsigned attribute_count = 1;

	// This specifies the number of varyings the shader will output. This is
	// for instance used when clipping.
	static const unsigned varying_count = 4;

	// This static function is called for each vertex to be processed.
	// "in" is an array of void* pointers with the location of the individial
	// vertex attributes. The "out" structure has to be written to.
	static void shade(const GeometryProcessor::VertexInput in, GeometryProcessor::VertexOutput &out)
	{
		// cast the first attribute array to the input vertex type
		const SoftwareColourVertex2d &v = *static_cast<const SoftwareColourVertex2d*>(in[0]);

		// x, y, z and w are the components that must be written by the vertex
		// shader. They all have to be specified in 16.16 fixed point format.
		out.x = static_cast<int>((v.vertex.x * (1 << 16)));
		out.y = static_cast<int>((v.vertex.y * (1 << 16)));
		out.z = 0;
		out.w = 1 << 16;

		// The vertexoutput can have up to Rasterizer::MAX_VARYING varying
		// parameters. These are just integer values which will be interpolated
		// across the primitives. The higher bits of these integers will be
		// interpolated more precicely so the values [0, 255] are shifted left.
		out.varyings[0] = v.colour.x << 16;
		out.varyings[1] = v.colour.y << 16;
		out.varyings[2] = v.colour.z << 16;
		out.varyings[3] = v.colour.w << 16;
	}
};

#endif // VERTEXBASIC2D_H_INCLUDED
