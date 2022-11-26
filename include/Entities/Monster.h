#pragma once

#include "Actions/Action.h"
#include "Character.h"

class Monster : public Character {
public:
    Monster(int id, World &world) : Character(id, nullptr, world) {}

    std::unique_ptr<Action> think() { return nullptr; } // TODO
};