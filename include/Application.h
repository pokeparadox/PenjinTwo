/**
    \section LICENSE
	PenjinTwo is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

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
*   \file Application is a base class to create certain application types.
*   \author Kevin Winfield-Pantoja
*/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Errors.h"
#include "LocalisedStringManager.h"
#include "StateManager.h"
using Penjin::LocalisedStringManager;


namespace Penjin
{

    /********** Forward Decalrations **********/
    class ApplicationState;

    /** \brief Application provides state management, cmmandline handling etc*/
    class Application : public Window
    {
        public:
            /** Default constructor */
            Application();
            /** Default destructor */
            virtual ~Application();

            /** \brief Processes commandline arguements
             * \param argc : an int of the number of commands
             * \param argv : the actual char** string data
             * \return Penjin::Errors : the error code.
             */
            virtual Penjin::ERRORS argHandler(int argc, char** argv);

            //void setNextState(StateID next);

            /** \brief Close down Penjin cleanly*/
            virtual void quit();

        protected:
            /** \brief Create a default settings file if not detected*/
            void createDefaultSettings();
            /** \brief Handle state switching*/
            void stateManagement();

            // StateID next;
            ApplicationState* state;    /**< The state of the application */
    };
}
#endif // APPLICATION_H
