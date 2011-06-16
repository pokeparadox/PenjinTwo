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
*   \file StateManager is a singleton class that you overide and build your state management.
*   \author Kevin Winfield-Pantoja
*/

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Singleton.h"
#include "ApplicationState.h"
#include <map>

namespace Penjin
{
    //class ApplicationState;

    class StateManager
    {
        public:
	    typedef int StateId;
	    static const StateId STATE_NULL = -1;

            /** Default constructor */
            StateManager();

            /** get a Singleton instance of this class! */
            static StateManager& getInstance()
            {
                static StateManager instanceSM;   // Instantiated when this function is called
                return instanceSM;
            }

            void addState(StateId id, ApplicationState* state);
            void setNextState(const StateId& next);
            StateId getCurrentState();
            void clearState();

            ApplicationState* getState();

            void stateManagement();
            void clear();
        private:
            StateManager(const StateManager& bling){;}
            StateManager& operator=(StateManager const&){return *this;}
            /** Default destructor */
            ~StateManager();

            ApplicationState* state;    /**< Actual state */
            StateId next;                /**< The ID of the next state to load.*/
            StateId current;             /**< The ID of the currently loaded state. */

            std::map<StateId, ApplicationState*> states;
    };
    typedef Singleton<StateManager> StateMan;
}
#endif // STATEMANAGER_H
