/*
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
*/#ifndef PANEL_H
#define PANEL_H

#include "Widget.h"
#include "UpdateObject.h"

namespace Penjin
{
    class Panel : public Widget, public UpdateObject
    {
        public:
            /** Default constructor */
            Panel();
            /** Default destructor */
            virtual ~Panel();

            virtual void render();
            virtual void update();

            // Change currently selected Widget on Panel
            void selectionNext();
            void selectionPrevious();
            // confirm the selection as active
            void selectionConfirm();

            // add a configured widget to the Panel
            void addWidget(Widget* w);

            template <class T>
            void setPosition(const T& pos)
            {
                Rectangle::setPosition(pos);
                startPosition.x = pos.x;
                startPosition.y = pos.y;
            }

            // return -1 if no Widget is active
            // otherwise return the index
            int whichWidget();

            bool isHidden();
            void toggleHidden();
            void setShouldHide(const bool& hide);

        protected:
            bool shouldHide;    //  retract the panel or not
            bool hidden;

            int selection;  // ID of the selected widget
            //int hideOffset;
            Vector2d<float> startPosition;

            /** We store all our widget pointers here**/
            vector<Widget*> widgets;
    };
}
#endif // PANEL_H
