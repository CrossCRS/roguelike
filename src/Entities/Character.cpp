#include "Entities/Character.h"

int Character::getCurrentAttribute(Attribute::Index index) const {
    if (index >= Attribute::LAST)
        throw std::invalid_argument("Invalid attribute index '" + std::to_string(index) + "'");

    return attributes[index].getCurrent();
}

int Character::getBaseAttribute(Attribute::Index index) const {
    if (index >= Attribute::LAST)
        throw std::invalid_argument("Invalid attribute index '" + std::to_string(index) + "'");

    return attributes[index].getBase();
}

void Character::setCurrentAttribute(Attribute::Index index, int value) {
    if (index >= Attribute::LAST)
        throw std::invalid_argument("Invalid attribute index '" + std::to_string(index) + "'");

    attributes[index].setCurrent(value);
    // TODO: Health checks
}

void Character::setBaseAttribute(Attribute::Index index, int value) {
    if (index >= Attribute::LAST)
        throw std::invalid_argument("Invalid attribute index '" + std::to_string(index) + "'");

    attributes[index].setBase(value);
}

float Character::getSpeed() const {
    return speed;
}

void Character::setSpeed(float newSpeed) {
    if (newSpeed < 0)
        throw std::invalid_argument("Character speed cannot be less than 0");

    speed = newSpeed;
}

const std::string &Character::getName() const {
    return name;
}

void Character::setName(const std::string &_name) {
    name = _name;
}
