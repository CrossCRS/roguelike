#pragma once

#include "Character.h"

#include <random>

class Action;

class Monster : public Character {
public:
    Monster(int id, World &world) : Character(id, nullptr, world),
                                    rd(), gen(rd()), distribution(0, 3) {}

    std::unique_ptr<Action> think();

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distribution;
};