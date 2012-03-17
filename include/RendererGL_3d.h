/**
	\section LICENSE
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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

#ifndef RENDERERGL_3D_H
#define RENDERERGL_3D_H

#if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2)

#include "RendererGL_2d.h"

namespace Penjin
{
    class RendererGL_3d : public RendererGL_2d
    {
        public:
            static RendererGL_3d* getInstance();
            /** Default constructor */
            RendererGL_3d();
            /** Default destructor */
            virtual ~RendererGL_3d();
        protected:
        private:
    };
}
#endif  //  GL or ES or ES2 only
#endif // RENDERERGL_3D_H
