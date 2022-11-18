#include "Entities/Character.h"

int Character::getMaxHealth() const {
    return maxHealth;
}

void Character::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;
    if (health > maxHealth) {
        health = maxHealth;
    }
}

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int newHealth) {
    health = (newHealth <= maxHealth ? newHealth : maxHealth);
}

float Character::getSpeed() const {
    return speed;
}

void Character::setSpeed(float newSpeed) {
    if (newSpeed < 0) {
        throw std::invalid_argument("Character speed cannot be less than 0");
    }
    speed = newSpeed;
}