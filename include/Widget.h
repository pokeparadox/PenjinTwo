/**
    \section
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
*/#ifndef WIDGET_H
#define WIDGET_H

#include "LayerObject.h"

namespace Penjin
{
    class Line;

    class Widget : public LayerObject
    {
        public:
            /** Default constructor */
            Widget();
            /** Default destructor */
            virtual ~Widget();

            virtual void render();

            // true if widget is active, false if not
            void setActive(const bool& a);
            bool isActive();
            // true if the widget is selected(not active), false otherwise.
            void setSelected(const bool& s);
            bool isSelected();

            void setLowLightColour(const Colour& c);
            void setHighLightColour(const Colour& c);
            void setSelectionColour(const Colour& c);

            void setShowHighLight(const bool& b);
            void setShowLowLight(const bool& b);
            void setShowSelection(const bool& b);
            void setShowWidget(const bool& b);

            bool isMouseSelected();
            bool isMouseActive();

        protected:

            Line* highLight;
            Line* lowLight;
            Colour* selectionColour;
            bool active;        // The the Widget is activated
            bool selected;      // if the widet is selected but not active

            bool showHighLight; // Show the lighted areas of a Widget
            bool showLowLight;  // Show the shadowed ares of a Widget
            bool showWidget;    // Show the Widget itself.
            bool showSelection; // Show the Selection of the Wdiget
    };
}
#endif // WIDGET_H
