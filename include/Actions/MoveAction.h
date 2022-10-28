#pragma once

#include "Action.h"
#include "Entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <utility>

class MoveAction : public Action {
public:
    MoveAction(std::shared_ptr<Entity> entity, sf::Vector2i moveDirection) : entity(std::move(entity)),
                                                                               moveDirection(moveDirection) {}

    void execute() override;

private:
    std::shared_ptr<Entity> entity;
    sf::Vector2i moveDirection;
};