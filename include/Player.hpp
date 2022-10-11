#pragma once

#include "Entity.hpp"

class Player : public Entity {
    public:
        Player(int id, ResourceManager& resourceManager) : Entity(id, "player", resourceManager) { }
};