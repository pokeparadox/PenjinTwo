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
**********************************************************************************************/
/**
  * \file WindowManager is a simple WindowManager to handle several instances of Window
  * \author Kevin Winfield-Pantoja
*/
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
//#include "Singleton.h"
#include "RenderObject.h"
#include "UpdateObject.h"
#include <vector>
using std::vector;
namespace Penjin
{
    class Window;

    class WindowManager : public RenderObject, public UpdateObject
    {
        public:
            /** Default constructor */
            WindowManager();
            /** Default destructor */
            virtual ~WindowManager();

            WindowManager* getInstance();

            /** \brief Render the relevent Window instances to the screen.*/
            virtual void render();

            /** \brief Update the relevent Window instances.*/
            virtual void update();


            /** \brief Add the pointer to a Window to nthe manager.
             * \param  win : The Window* to add.
             */
            void add(Window* win);

            /** \brief Minimise all Windows*/
            void minimise();

            /** \brief Clear out the window pointers.*/
            void clear();

        protected:
            vector<Window*> windows;
        private:
            static WindowManager* instance;
    };
    //typedef Singleton<WindowManager> WinMan;
    typedef WindowManager WinMan;
}
#endif // WINDOWMANAGER_H
