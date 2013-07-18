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
*   \file Texture is a class to handle the storage of hardware accelerated  images normally stored in GFX RAM
*   \author Kevin Winfield-Pantoja
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include "RenderObject.h"
#include "DimensionObject.h"
#include "Errors.h"

namespace Penjin
{
    class Surface;

    class Texture : public RenderObject, DimensionObject
    {
        public:
            /** Default constructor */
            Texture();
            /** Default destructor */
            virtual ~Texture();

            /** \brief Load a Penjin Surface into GFX RAM as a Texture.
             * \param s : the pointer to a surface to load.
             * \return Penjin::Errors : the error code.
             */
            Penjin::ERRORS load(Surface* s);

            /** \brief States if texture is still in GFX RAM.
             * \return true if still present, false if RAM has been freed.
             */
            bool isLoaded();

            /** \brief Set the ID of an externally created texture to allow the Texture class to handle it.
             * \param ID : the identifier of the created texture.
             */
            void setTexture(const unsigned int& ID );

            /** \brief Gets the identifier of the loaded Texture.
             * \return the identifier.
             */
            unsigned int getTexture();

            /** \brief Gets the coordinates of this texture.
             * \return the coordinates.
             */
            Vector2d<float> getTextureCoords();



        protected:
            Vector2d<float> txCoords;       //  Stores the calculated Texture coordinates.
            unsigned int txID;              //  Stores the identifier of the Texture.
            bool loaded;                    //  Stores if the Texture is in GFX RAM or not.
        private:
    };
}



#endif // TEXTURE_H
