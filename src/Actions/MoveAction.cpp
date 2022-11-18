#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = character->getGridPosition() + moveDirection;
    auto &newTile = character->getTileMap().getTile(newPos);

    if (!newTile.isImpenetrable()) {
        character->setGridPosition(newPos);
    }

    newTile.interact(*character);
}