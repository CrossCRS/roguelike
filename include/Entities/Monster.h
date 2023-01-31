#pragma once

#include "Character.h"

class Action;

class Monster : public Character {
public:
    Monster(int id, World &world) : Character(id, nullptr, world) {}

    std::unique_ptr<Action> think();
};