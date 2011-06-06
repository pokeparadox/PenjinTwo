#ifndef SIMPLE_DIRECTION_H
#define SIMPLE_DIRECTION_H

#include "PenjinTypes.h"
#include "Vector2d.h"

namespace Penjin
{
enum Directions
{
    diNONE=0,
    diLEFT,
    diRIGHT,
    diTOP,
    diBOTTOM,
    diTOPLEFT,
    diTOPRIGHT,
    diBOTTOMLEFT,
    diBOTTOMRIGHT,
    diMIDDLE
};

class SimpleDirection
{
public:
    SimpleDirection()
    {
        value = diNONE;
    }
    SimpleDirection(CRint init)
    {
        value = checkIntValue(init);
    }
    // TODO: Add class constructor taking a vector

    virtual ~SimpleDirection() {}

    // Returns the opposite direction of this->value
    virtual SimpleDirection opposite() const
    {
        return SimpleDirection(getOpposite(value));
    }

    // Returns an integer describing the direction
    virtual int xDirection() const; // -1 - left, 0 - none, 1 - right
    virtual int yDirection() const; // -1 - up, 0 - none 1 - down
    virtual Vector2d<int> vectorDirection() const;

    // Comparison operators
    bool operator==(const SimpleDirection& dir) const
    {
        return (this->value == dir.value);
    }
    template <class T>
    bool operator==(const T& dir) const
    {
        return (this->value == dir);
    }

    bool operator!=(const SimpleDirection& dir) const
    {
        return (this->value != dir.value);
    }
    template <class T>
    bool operator!=(const T& dir) const
    {
        return (this->value != dir);
    }

    // comparison operators for use with map
    bool operator<(const SimpleDirection& dir) const
    {
        return (this->value < dir.value);
    }
    bool operator>(const SimpleDirection& dir) const
    {
        return (this->value > dir.value);
    }

    // Negator
    SimpleDirection operator-() const
    {
        return this->opposite();
    }

    int value; // the actual value
protected:
    // Checks whether the passed value is valid and returns it, returns diNONE otherwise
    virtual int checkIntValue(CRint newValue) const;
    // Returns the opposite direction of the one passed
    virtual int getOpposite(CRint someValue) const;
};

};

#endif
