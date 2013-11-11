#ifndef SHADERLIST_H_INCLUDED
#define SHADERLIST_H_INCLUDED

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
*   \file ShaderList is List of internal shaders for the software renderer
*   \author Kevin Winfield-Pantoja
*/
namespace Penjin
{
    enum VERTEX_SHADER_LIST
    {
        VSL_BASIC_2D,
    };

    enum FRAGMENT_SHADER_LIST
    {
        FSL_BASIC,

    };

}
    #include "trenki/renderer/geometry_processor.h"
    #include "trenki/renderer/rasterizer_subdivaffine.h"
    #include "trenki/renderer/span.h"
    #include "PenjinTypes.h"
    #include "FragmentBasic.h"
    #include "VertexBasic2d.h"
#endif // SHADERLIST_H_INCLUDED
