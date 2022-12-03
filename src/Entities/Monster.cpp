#include "Entities/Monster.h"

#include "Actions/Action.h"
#include "Actions/MoveAction.h"

std::unique_ptr<Action> Monster::think() {
    // TODO: Proper AI
    sf::Vector2i direction;

    int dir = distribution(gen);
    switch (dir) {
        case 0:
            direction = sf::Vector2i(0, -1);
            break;
        case 1:
            direction = sf::Vector2i(1, 0);
            break;
        case 2:
            direction = sf::Vector2i(0, 1);
            break;
        case 3:
            direction = sf::Vector2i(-1, 0);
            break;
        default:
            break;
    }

    return std::make_unique<MoveAction>(*this, direction);
}