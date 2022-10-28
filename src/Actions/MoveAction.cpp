#include "Actions/MoveAction.h"

void MoveAction::execute() {
    // TODO: Collision detection
    this->entity->setGridPosition(this->entity->getGridPosition() + this->moveDirection);
}