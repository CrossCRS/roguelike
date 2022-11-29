#include "Attribute.h"

Attribute::Attribute(int _current, int _base) : current(_current), base(_base) {}
Attribute::Attribute() : Attribute(1, 1) {}

int Attribute::getCurrent() const {
    return current;
}

int Attribute::getBase() const {
    return base;
}

void Attribute::setCurrent(int value) {
    if (value < 0) {
        current = 0;
    } else {
        current = value;
    }
}

void Attribute::setBase(int value) {
    if (value < 0) {
        base = 0;
    } else {
        base = value;
    }
}