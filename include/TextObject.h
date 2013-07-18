#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "Object.h"
#include <string>
using std::string;

namespace Penjin
{
    class TextObject : public Object
    {
        public:
            TextObject();
            virtual ~TextObject();

            void  setText(const std::string& txt);
            std::string getText()const;

        protected:
            std::string text;
    };
}
#endif // TEXTOBJECT_H
