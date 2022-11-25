#pragma once

#include "Character.h"

class Player : public Character {
public:
    Player(int id, std::shared_ptr<sf::Texture> texture, World &world) : Character(id, std::move(texture), world) {}
};