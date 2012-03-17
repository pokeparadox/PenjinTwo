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
/***************************************************************************************************
*   \file StateManager is a class that handles the switching of gamestates
*   \author Kevin Winfield-Pantoja
*/

#include "ApplicationState.h"
#include "StateManager.h"
using Penjin::StateManager;
using Penjin::ApplicationState;

//StateManager* StateManager::instance = NULL;

StateManager::StateManager() : state(NULL), next(STATE_NULL), current(STATE_NULL), states()
{
    //ctor
}

StateManager::~StateManager()
{
    //dtor
    clearState();
    clear();
}

/*StateManager* StateManager::getInstance()
{
    if( instance == NULL )
    {
        instance = new StateManager;
    }
    return instance;
}*/

void StateManager::addState(StateId id, ApplicationState* state)
{
    states[id] = state;
}
void StateManager::setNextState(const StateId& s)
{
    next = s;
}

void StateManager::stateManagement()
{
    if(next != current && states.find(next) != states.end())
    {
        // Clear out current state (if exists)
        if(state)
            state->clear();
        // Swap state
        state = states[next];
        // Setup State
        state->init();
        current = next;
    }
}

StateManager::StateId StateManager::getCurrentState()
{
    return current;
}

ApplicationState* StateManager::getState()
{
    return state;
}


void StateManager::clearState()
{
    current = STATE_NULL;
    state = NULL;
}

void StateManager::clear()
{
    for(uint i = 0; i < states.size(); ++i)
    {
        delete states[i];
    }
}
