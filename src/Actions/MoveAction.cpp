#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = character.getGridPosition() + moveDirection;
    auto &newTile = character.getWorld().getMap().getTile(newPos);

    if (!newTile.isImpenetrable()) {
        if (character.getWorld().getMonsterOnPos(newPos) == nullptr
            && character.getWorld().getPlayer().getGridPosition() != newPos) {
            character.setGridPosition(newPos);
        } else {
            // TODO: Execute attack action instead?
        }
    }

    newTile.interact(character);
}