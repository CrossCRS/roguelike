#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(int id, ResourceManager &resourceManager, TileMap &tilemap) : Entity(id, "player", resourceManager, tilemap) {}
};