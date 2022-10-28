#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = entity->getGridPosition() + moveDirection;

    try {
        if (entity->getTileMap().canWalk(newPos)) {
            entity->setGridPosition(newPos);
        }
    } catch (const std::invalid_argument&) {} // Out of map
}