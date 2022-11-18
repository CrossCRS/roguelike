#pragma once

#include "Entity.h"

class Character : public Entity {
public:
    Character(int id, std::shared_ptr<sf::Texture> texture, TileMap &tilemap) :
        Entity(id, std::move(texture), tilemap),
        maxHealth(100),
        health(100),
        speed(1.f) {}

    int getMaxHealth() const;
    void setMaxHealth(int newMaxHealth);

    int getHealth() const;
    void setHealth(int newHealth);

    float getSpeed() const;
    void setSpeed(float newSpeed);
private:
    // TODO: Attributes class?
    int maxHealth;
    int health;

    float speed;
};