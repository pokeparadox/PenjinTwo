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
*/#ifndef RENDERERSDL_3D_H
#define RENDERERSDL_3D_H

#include "RendererSDL_2d.h"
#include "shaders/ShaderList.h"

namespace Penjin
{


    class RendererSDL_3d : public RendererSDL_2d
    {
        public:
            /** Default constructor */
            RendererSDL_3d();
            /** Default destructor */
            virtual ~RendererSDL_3d();

             /** Sets the currently set width, height and bit-depth to the screen */
            virtual void applyVideoSettings();
            //  Sets the 3D renderer to a basic 2D projection
            virtual void applyVideoSettings2d();
            //  Sets the £D renderer to a basic 3D projection
            virtual void applyVideoSettings3d();

            void setVertexShader(VERTEX_SHADER_LIST selectedList);
            void setFragmentShader(FRAGMENT_SHADER_LIST selectedList);


            void setVertexPointer(int n, int stride, const void* buffer);
            void drawTriangles(unsigned count, unsigned *indices);



        protected:
            RasterizerSubdivAffine* rasterizer;
            GeometryProcessor* geometryProcessor;
        private:
    };
}
#endif // RENDERERSDL_3D_H
