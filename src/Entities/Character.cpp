#include "Entities/Character.h"

int Character::getCurrentAttribute(AttributeIndex index) const {
    return attributes[static_cast<int>(index)].getCurrent();
}

int Character::getBaseAttribute(AttributeIndex index) const {
    return attributes[static_cast<int>(index)].getBase();
}

void Character::setCurrentAttribute(AttributeIndex index, int value) {
    attributes[static_cast<int>(index)].setCurrent(value);
    // TODO: Health checks
}

void Character::setBaseAttribute(AttributeIndex index, int value) {
    attributes[static_cast<int>(index)].setBase(value);
}

float Character::getSpeed() const {
    return speed;
}

void Character::setSpeed(float newSpeed) {
    if (newSpeed < 0)
        throw std::invalid_argument("Character speed cannot be less than 0");

    speed = newSpeed;
}

bool Character::canInteractWithObjects() const {
    return bcanInteractWithObjects;
}

void Character::setCanInteractWithObjects(bool value) {
    bcanInteractWithObjects = value;
}

const std::string &Character::getName() const {
    return name;
}

void Character::setName(const std::string &_name) {
    name = _name;
}
