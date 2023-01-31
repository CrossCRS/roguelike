#include "Actions/ActionQueue.h"

#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

void ActionQueue::addAction(std::unique_ptr<Action> action) {
    queue.push(std::move(action));
}

void ActionQueue::setPlayerAction(std::unique_ptr<Action> action) {
    playerAction = std::move(action);
}

void ActionQueue::processActions() {
    while (!queue.empty()) {
        auto action = std::move(queue.front());
        queue.pop();

        if (action != nullptr) {
            const float speed = action->getSpeed();
            const int actions = static_cast<int>(speed);
            const float chanceForExtraAction = speed - actions;

            // Execute the guaranteed actions
            for (int j = 0; j < actions; j++) {
                action->execute();
            }

            // Execute the extra action
            if (Random::get(0.f, 1.f) < chanceForExtraAction) {
                action->execute();
            }
        }
    }
}

bool ActionQueue::processPlayerAction() {
    if (playerAction == nullptr) return false;

    playerAction->execute();
    playerAction = nullptr;
    return true;
}