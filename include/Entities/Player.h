#pragma once

#include "Character.h"

class Player : public Character {
public:
    Player(int id, std::shared_ptr<sf::Texture> texture, TileMap &tilemap) : Character(id, std::move(texture), tilemap) {}
};