#include "Entities/Character.h"

#include "Map/World.h"

#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif

bool Character::isPlayer() const {
    return false;
}

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

Inventory &Character::getInventory() {
    return inventory;
}

void Character::onDamageTaken(Entity *source, int damage) {
    auto character = dynamic_cast<Character*>(source);
    if (damage >= getCurrentAttribute(AttributeIndex::HEALTH)) {
        if (character != nullptr) {
            character->addExperience(experienceForKill);
        }
        onDeath();
    } else {
        setCurrentAttribute(AttributeIndex::HEALTH, getCurrentAttribute(AttributeIndex::HEALTH) - damage);
    }
}

void Character::onDeath() {
    // TODO: Drop some item?
    getWorld().removeMonster(getId());
}

void Character::setLevel(int _level) {
    if (_level > 1) {
        level = _level - 1;
        experience = getExperienceForNextLevel() + 1;
        level = _level;
    } else {
        level = _level;
        experience = 0;
    }
}

void Character::setExperienceForKill(int exp) {
    experienceForKill = exp;
}

int Character::getLevel() const {
    return level;
}

int Character::getExperience() const {
    return experience;
}

int Character::getAttributePoints() const {
    return attributePoints;
}

int Character::getExperienceForKill() const {
    return experienceForKill;
}

int Character::getExperienceForNextLevel() const {
    return 15 * level * (level + 1);
}

void Character::addExperience(int exp) {
    experience += exp;
    while (experience >= getExperienceForNextLevel()) {
        levelUp();
    }
}

void Character::levelUp() {
    attributePoints++;
    level++;

    // Gain 10 HP every 5 levels
    if (level % 5 == 0) {
        setBaseAttribute(AttributeIndex::HEALTH, getBaseAttribute(AttributeIndex::HEALTH) + 10);
        setCurrentAttribute(AttributeIndex::HEALTH, getBaseAttribute(AttributeIndex::HEALTH));
    }
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = texture.get();
    target.draw(vertices, states);

    if (!isPlayer())
        target.draw(*guiHealthBar, states);
}

void Character::update() {
    if (!isPlayer())
        guiHealthBar->update();
}
