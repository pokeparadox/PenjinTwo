#include "SimpleDirection.h"

using Penjin::SimpleDirection;
using Penjin::Vector2d;

int SimpleDirection::xDirection() const
{
    switch(this->value)
    {
    case diLEFT:
    case diTOPLEFT:
    case diBOTTOMLEFT:
        return -1;
    case diRIGHT:
    case diTOPRIGHT:
    case diBOTTOMRIGHT:
        return 1;
    default:
        return 0;
    }
}

int SimpleDirection::yDirection() const
{
    switch(this->value)
    {
    case diTOP:
    case diTOPLEFT:
    case diTOPRIGHT:
        return -1;
    case diBOTTOM:
    case diBOTTOMLEFT:
    case diBOTTOMRIGHT:
        return 1;
    default:
        return 0;
    }
}

Vector2d<int> SimpleDirection::vectorDirection() const
{
    return Vector2d<int>(xDirection(),yDirection());
}

int SimpleDirection::checkIntValue(CRint newValue) const
{
    if (newValue < 0)
        return diNONE;
    else if (newValue > diMIDDLE) // NOTE: This might need to be changed when more directions are added
        return diNONE;
    return newValue;
}

int SimpleDirection::getOpposite(CRint someValue) const
{
    switch(someValue)
    {
    case diLEFT:
        return diRIGHT;
    case diRIGHT:
        return diLEFT;
    case diTOP:
        return diBOTTOM;
    case diBOTTOM:
        return diTOP;
    case diTOPLEFT:
        return diBOTTOMRIGHT;
    case diTOPRIGHT:
        return diBOTTOMLEFT;
    case diBOTTOMLEFT:
        return diTOPRIGHT;
    case diBOTTOMRIGHT:
        return diTOPLEFT;
    case diMIDDLE:
        return diMIDDLE;
    default:
        return diNONE;
    }
}
