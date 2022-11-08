#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = entity->getGridPosition() + moveDirection;

    auto &newTile = entity->getTileMap().getTile(newPos);

    if (!newTile.isImpenetrable()) {
        entity->setGridPosition(newPos);
    }

    newTile.interact(*entity);
}