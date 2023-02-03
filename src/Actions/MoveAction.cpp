#include "Actions/MoveAction.h"

#include "Actions/AttackAction.h"
#include "Entities/GroundItem.h"
#include "Entities/Player.h"
#include "Map/TileMap.h"
#include "Map/World.h"
#include "Map/Tiles/BaseTile.h"

void MoveAction::execute() {
    // TODO: Better collision detection
    sf::Vector2i newPos = character->getGridPosition() + moveDirection;
    auto &newTile = character->getWorld().getMap().getTile(newPos);

    if (!newTile.isImpenetrable()) {
        if (character->getWorld().getMonsterOnPos(newPos) == nullptr
            && character->getWorld().getPlayer()->getGridPosition() != newPos) {
            character->setGridPosition(newPos);
        } else if (character->getWorld().getMonsterOnPos(newPos) != nullptr && character->isPlayer()) { // Monsters must attack explicitly!
            AttackAction(character, character->getWorld().getMonsterOnPos(newPos)).execute();
        }

        // TODO: Item pickup GUI?
        auto groundItem = dynamic_cast<GroundItem*>(character->getWorld().getEntityOnPos(newPos));
        if (groundItem != nullptr) {
            character->getInventory().addItem(std::move(groundItem->item));
            character->getWorld().getEntityManager().removeEntity(*groundItem);
        }
    }

    if (character->canInteractWithObjects()) {
        newTile.interact(character);
    }
}