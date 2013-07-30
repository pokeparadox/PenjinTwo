#include "WidgetCollection.h"
#include "Widget.h"
using Penjin::WidgetCollection;
using Penjin::Widget;
WidgetCollection::WidgetCollection()
{
    //ctor
}

WidgetCollection::~WidgetCollection()
{
    //dtor
     clear();
}


void WidgetCollection::clear()
{
    for(int i = widgets.size()-1; i>=0; --i)
    {
        delete widgets.at(i);
        widgets.at(i) = NULL;
    }
    widgets.clear();
}

void WidgetCollection::add(Widget* w)
{
    if(w != NULL)
        widgets.push_back(w);
}

Widget* WidgetCollection::getWidest()
{
    int width = 0;
    int index = 0;
    for(int i = size()-1; i >= 0;--i)
    {
        if(widgets.at(i)->getWidth() > width)
        {
            index = i;
            width = widgets.at(i)->getWidth();
        }
    }
    return widgets.at(index);
}

Widget* WidgetCollection::getTallest()
{

}
