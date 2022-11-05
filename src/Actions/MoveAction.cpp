#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = entity->getGridPosition() + moveDirection;

    if (!entity->getTileMap().getTile(newPos).isImpenetrable()) {
        entity->setGridPosition(newPos);
    }
}