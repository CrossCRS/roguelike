#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = entity->getGridPosition() + moveDirection;

    if (entity->getTileMap().canWalk(newPos)) {
        entity->setGridPosition(newPos);
    }
}