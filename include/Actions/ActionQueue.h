#pragma once

#include "Actions/Action.h"
#include "Entities/Character.h"
#include "Entities/Player.h"

#include <random>
#include <queue>

// PREDKOSC GRACZA ZAWSZE 1
// Predkosc 1 - gwarantowany 1 ruch na ture
// Predkosc 2 - gwarantowane 2 ruchy na ture
// Predkosc 1.75 - gwarantowany 1 ruch, 75% szans na drugi
// Predkosc 0.75 - 75% szans na 1 ruch
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