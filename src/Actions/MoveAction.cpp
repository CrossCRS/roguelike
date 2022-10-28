#include "Actions/MoveAction.h"

void MoveAction::execute() {
    sf::Vector2i offset(0, 0);

    switch (this->moveDirection) {
        case UP:
            offset.y = -1;
            break;
        case RIGHT:
            offset.x = 1;
            break;
        case DOWN:
            offset.y = 1;
            break;
        case LEFT:
            offset.x = -1;
            break;
        case NONE:
        default:
            break;
    }

    this->entity->setGridPosition(this->entity->getGridPosition() + offset);
}