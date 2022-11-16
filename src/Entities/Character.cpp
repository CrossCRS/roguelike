#include "Entities/Character.h"

int Character::getMaxHealth() const {
    return maxHealth;
}

int Character::getHealth() const {
    return health;
}

void Character::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;
    if (health > maxHealth) {
        health = maxHealth;
    }
}
void Character::setHealth(int newHealth) {
    health = (newHealth <= maxHealth ? newHealth : maxHealth);
}