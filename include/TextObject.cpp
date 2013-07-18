#include "TextObject.h"
using Penjin::TextObject;


TextObject::TextObject()
{
    //ctor
}

TextObject::~TextObject()
{
    //dtor
}

void TextObject::setText(const std::string& str)
{
    text = str;
}

std::string TextObject::getText()const
{
    return text;
}

