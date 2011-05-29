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
**********************************************************************************************/
/**
  * \file SpriteButton is a class to create a button with an image centred on button face.
  * \author Kevin Winfield-Pantoja
*/#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H

#include "Button.h"
#include "Errors.h"

namespace Penjin
{
    class Sprite;

    class SpriteButton : public Button
    {
        public:
            /** Default constructor */
            SpriteButton();
            /** Default destructor */
            virtual ~SpriteButton();

            virtual void render();
            virtual void update();

            Penjin::ERRORS loadImage(const string& file);
            void clearImage();

        protected:
            Sprite* sprite;
        private:
    };
}


#endif // SPRITEBUTTON_H
