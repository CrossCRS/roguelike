#pragma once

#include "Action.h"

#include <memory>
#include <queue>

class ActionQueue {
public:
    ActionQueue() : playerAction(nullptr) {}

    void addAction(std::unique_ptr<Action> action);
    void setPlayerAction(std::unique_ptr<Action> action);

    void processActions();
    bool processPlayerAction();
private:
    std::queue<std::unique_ptr<Action>> queue;
    std::unique_ptr<Action> playerAction;
};