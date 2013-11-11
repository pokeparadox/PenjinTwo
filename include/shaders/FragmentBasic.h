#ifndef FRAGMENTBASIC_H_INCLUDED
#define FRAGMENTBASIC_H_INCLUDED

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
#include "trenki/renderer/geometry_processor.h"
#include "trenki/renderer/rasterizer_subdivaffine.h"
#include "trenki/renderer/span.h"
using namespace swr;


// This is the fragment shader

struct FragmentBasicRGB : public SpanDrawer16BitColorAndDepth<FragmentBasicRGB> {

	// varying_count = 3 tells the rasterizer that it only needs to interpolate
	// three varying values (the r, g and b in this context).
	static const unsigned varying_count = 3;

	// We don't need to interpolate z in this example
	static const bool interpolate_z = false;

	// Per triangle callback. This could for instance be used to select the
	// mipmap level of detail. We don't need it but it still needs to be defined
	// for everything to work.
	static void begin_triangle(
		const IRasterizer::Vertex& v1,
		const IRasterizer::Vertex& v2,
		const IRasterizer::Vertex& v3,
		int area2)
	{}


	// the fragment shader is called for each pixel and has read/write access to
	// the destination color and depth buffers.
	static void single_fragment(
		const IRasterizer::FragmentData &fd,
		unsigned short &color,
		unsigned short &depth)
	{
		SDL_Surface *screen = SDL_GetVideoSurface();

		// Convert from 16.16 color format to [0,255]
		// Here the colors are clamped to the range[0,255]. If this is not done
		// here we can get very small artifacts at the edges.
		int r = std::min(std::max(fd.varyings[0] >> 16, 0), 255);
		int g = std::min(std::max(fd.varyings[1] >> 16, 0), 255);
		int b = std::min(std::max(fd.varyings[2] >> 16, 0), 255);
		color = SDL_MapRGB(screen->format, r, g, b);
	}

	// this is called by the span drawing function to get the location of the color buffer
	static void* color_pointer(int x, int y)
	{
		SDL_Surface *screen = SDL_GetVideoSurface();
		return static_cast<unsigned short*>(screen->pixels) + x + y * screen->w;
	}

	// this is called by the span drawing function to get the location of the depth buffer
	static void* depth_pointer(int x, int y)
	{
		// We don't use a depth buffer
		return 0;
	}

};


// This is the fragment shader

struct FragmentBasicRGBA : public SpanDrawer16BitColorAndDepth<FragmentBasicRGBA> {

	// varying_count = 3 tells the rasterizer that it only needs to interpolate
	// three varying values (the r, g , b and a in this context).
	static const unsigned varying_count = 4;

	// We don't need to interpolate z in this example
	static const bool interpolate_z = false;

	// Per triangle callback. This could for instance be used to select the
	// mipmap level of detail. We don't need it but it still needs to be defined
	// for everything to work.
	static void begin_triangle(
		const IRasterizer::Vertex& v1,
		const IRasterizer::Vertex& v2,
		const IRasterizer::Vertex& v3,
		int area2)
	{}


	// the fragment shader is called for each pixel and has read/write access to
	// the destination color and depth buffers.
	static void single_fragment(
		const IRasterizer::FragmentData &fd,
		unsigned short &colour,
		unsigned short &depth)
	{
		SDL_Surface *screen = SDL_GetVideoSurface();

		// Convert from 16.16 color format to [0,255]
		// Here the colors are clamped to the range[0,255]. If this is not done
		// here we can get very small artifacts at the edges.
		int r = std::min(std::max(fd.varyings[0] >> 16, 0), 255);
		int g = std::min(std::max(fd.varyings[1] >> 16, 0), 255);
		int b = std::min(std::max(fd.varyings[2] >> 16, 0), 255);
		int a = std::min(std::max(fd.varyings[3] >> 16, 0), 255);
		colour = SDL_MapRGBA(screen->format, r, g, b, a);
	}

	// this is called by the span drawing function to get the location of the color buffer
	static void* color_pointer(int x, int y)
	{
		SDL_Surface *screen = SDL_GetVideoSurface();
		return static_cast<unsigned short*>(screen->pixels) + x + y * screen->w;
	}

	// this is called by the span drawing function to get the location of the depth buffer
	static void* depth_pointer(int x, int y)
	{
		// We don't use a depth buffer
		return 0;
	}

};

#endif // FRAGMENTBASIC_H_INCLUDED
