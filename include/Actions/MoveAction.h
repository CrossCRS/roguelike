#pragma once

#include "Action.h"
#include "Entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <utility>

enum MOVE_DIRECTION {
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class MoveAction : public Action {
public:
    MoveAction(std::shared_ptr<Entity> entity, MOVE_DIRECTION moveDirection) : entity(std::move(entity)),
                                                                               moveDirection(moveDirection) {}

    void execute() override;

private:
    std::shared_ptr<Entity> entity;
    MOVE_DIRECTION moveDirection;
};