#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(int id, ResourceManager &resourceManager) : Entity(id, "player", resourceManager) {}
};