/**
    \section LICENSE
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

	This file is part of PenjinTwo.

	PenjinTwo is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	PenjinTwo is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with PenjinTwo.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
  * \file Game is a base class for creating a game.
  * \author Kevin Winfield-Pantoja
  */
#ifndef GAME_H
#define GAME_H

#include "Application.h"

namespace Penjin
{
    class Game : public Application
    {
        public:
            /** Default constructor */
            Game();
            /** Default destructor */
            virtual ~Game();

            //virtual void update()=0;
            virtual void loop();    /**< The main game loop */
        protected:
            /** \brief Attempts to load the config file from the default location.
             * \return The error in trying to load the config file
             */
            Penjin::ERRORS loadConfig();
    };
}
#endif // GAME_H
