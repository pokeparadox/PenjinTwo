#ifndef WIDGETCOLLECTION_H
#define WIDGETCOLLECTION_H

#include "Widget.h"
namespace Penjin
{
    class WidgetCollection : public Widget
    {
        public:
            /** Default constructor */
            WidgetCollection();
            /** Default destructor */
            virtual ~WidgetCollection();

                        // add a configured widget to the Panel
            void add(Widget* w);
            void edit(const unsigned int& i, Widget* w);
            void remove(const unsigned int& i);
            Widget* at(const unsigned int& i);

            Widget* getWidest();
            Widget* getTallest();

            /// Size operations
            size_t size()const{return widgets.size();}
            bool empty()const{return !size();}
            void clear();

        protected:
            /** We store all our widget pointers here**/
            vector<Widget*> widgets;
    };

}


#endif // WIDGETCOLLECTION_H
