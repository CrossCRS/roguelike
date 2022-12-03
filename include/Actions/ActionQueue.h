#pragma once

#include "Action.h"

#include <random>
#include <queue>

class ActionQueue {
public:
    ActionQueue() : playerAction(nullptr), rd(), gen(rd()), distribution(0, 1) {}

    void addAction(std::unique_ptr<Action> action);
    void setPlayerAction(std::unique_ptr<Action> action);

    void processActions();
    bool processPlayerAction();
private:
    std::queue<std::unique_ptr<Action>> queue;
    std::unique_ptr<Action> playerAction;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> distribution;
};