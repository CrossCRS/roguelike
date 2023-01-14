#include "Actions/MoveAction.h"

#include "Entities/GroundItem.h"
#include "Entities/Player.h"
#include "Map/TileMap.h"
#include "Map/World.h"
#include "Map/Tiles/BaseTile.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = character.getGridPosition() + moveDirection;
    auto &newTile = character.getWorld().getMap().getTile(newPos);

    if (!newTile.isImpenetrable()) {
        if (character.getWorld().getMonsterOnPos(newPos) == nullptr
            && character.getWorld().getPlayer().getGridPosition() != newPos) {
            character.setGridPosition(newPos);
        } else if (character.getWorld().getMonsterOnPos(newPos) != nullptr) {
            // TODO: Execute attack action instead?
        }

        // TODO: Item pickup, GUI later?
        auto item = dynamic_cast<GroundItem*>(character.getWorld().getEntityOnPos(newPos));
        if (item != nullptr) {

        }
    }

    if (character.canInteractWithObjects()) {
        newTile.interact(character);
    }
}