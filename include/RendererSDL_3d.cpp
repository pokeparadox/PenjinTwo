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

#include "RendererSDL_3d.h"
#include "ConfigManager.h"
// requires software renderer source



using Penjin::RendererSDL_3d;

RendererSDL_3d::RendererSDL_3d()
{
    //ctor
    //  Report all features of the renderer
    ConfigMan::getInstance()->report("GFXSDL");
    ConfigMan::getInstance()->report("GFX2D");
    ConfigMan::getInstance()->report("GFX3D");

    //  Setup SW 3D Renderer
    rasterizer = new RasterizerSubdivAffine;
    geometryProcessor = new GeometryProcessor(rasterizer);
}

RendererSDL_3d::~RendererSDL_3d()
{
    //dtor
   delete rasterizer;
   delete geometryProcessor;
}

void RendererSDL_3d::applyVideoSettings()
{
    //  We create a normal SDL window first
    RendererSDL_2d::applyVideoSettings();

    // it is necessary to set the viewport
	geometryProcessor->viewport(0, 0, screen->w, screen->h);
	// set the cull mode (CW is already the default mode)
	geometryProcessor->cull_mode(GeometryProcessor::CULL_CW);

	// it is also necessary to set the clipping rectangle
	rasterizer->clip_rect(0, 0, screen->w, screen->h);
}

void RendererSDL_3d::applyVideoSettings2d()
{
    //applyVideoSettings();
    //  Setup default vertex and frag shader
    setVertexShader(VSL_BASIC_2D);
    setFragmentShader(FSL_BASIC);
}

void RendererSDL_3d::applyVideoSettings3d()
{
//applyVideoSettings();
    //  Setup default 3D projection
    //  SetVertexShader(VSL_BASIC_3D);
    //  SetFragmentShader(FSL_BASIC_3D);
}

void RendererSDL_3d::setVertexShader(VERTEX_SHADER_LIST selectedList)
{
    // Set the vertex shader
    if(selectedList == VSL_BASIC_2D)
        geometryProcessor->vertex_shader<VertexBasic2d_RGBA>();

}
void RendererSDL_3d::setFragmentShader(FRAGMENT_SHADER_LIST selectedList)
{
    // Set the fragment shader
    if(selectedList == FSL_BASIC)
        rasterizer->fragment_shader<FragmentBasicRGBA>();
}

void RendererSDL_3d::setVertexPointer(int n, int stride, const void* buffer)
{
    	// Specify where out data lies in memory
	geometryProcessor->vertex_attrib_pointer(n, stride, buffer);

}

void RendererSDL_3d::drawTriangles(unsigned count, unsigned *indices)
{
	// draw the triangle
	geometryProcessor->draw_triangles(count, indices);
}
