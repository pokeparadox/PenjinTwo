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
*   \file StateManager is a class that handles the switching of gamestates
*   \author Kevin Winfield-Pantoja
*/

#include "ApplicationState.h"
#include "StateManager.h"
using Penjin::StateManager;
using Penjin::ApplicationState;

StateManager::StateManager() : state(NULL), next(STATE_EXAMPLE), current(STATE_NULL)
{
    //ctor
}

StateManager::~StateManager()
{
    //dtor
    clearState();
}

void StateManager::setNextState(const STATES& s)
{
    next = s;
}

void StateManager::stateManagement()
{
    if(next != current)
    {
        delete state;
        switch(next)
        {
            case STATE_EXAMPLE:
            {
                state = new StateExample;
                break;
            }
            /*  Add code as STATE_EXAMPLE for your customs states in file below
            */
            #include "MyStateChangeCode.h"
            /*  Generally speaking do not edit below.
            */
            default:
            {
                //  The example State also doubles as an error state
                state = new StateExample;
                break;
            }
        }
        current= next;
    }
}

Penjin::STATES StateManager::getCurrentState()
{
    return current;
}

ApplicationState* StateManager::getState()
{
    return state;
}


void StateManager::clearState()
{
    delete state;
    state=NULL;
}
