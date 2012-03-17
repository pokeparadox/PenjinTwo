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
/** \file ApplicationState is a base class to create application states for your application or game.
*   It is not to be instantiated directly!
*   \author Kevin Winfield-Pantoja
*/
#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include "RenderObject.h"
#include "UpdateObject.h"
#include "SimpleJoy.h"

namespace Penjin
{
    class ApplicationState : public RenderObject, public UpdateObject
    {
        public:
            /** Default constructor */
            ApplicationState();
            /** Default destructor */
            virtual ~ApplicationState();

            /**< \brief Setup the state, called by the StateManager. */
            virtual void init()=0;
            /**< \brief Shutdown state on state switch, called by StateManager. */
            virtual void clear()=0;

            /**< \brief Handle user input. */
            virtual void input()=0;
            /**< \brief Update this state. */
            virtual void update()=0;
            /**<    \brief Check if the state requests to quit or not.
                    \return true if the state would like to quit and false if not.*/
            bool getShouldQuit()const;

        protected:
            bool shouldQuit;    /**< the bool if the state would like to quit. */
    };
}
#endif // APPLICATIONSTATE_H
