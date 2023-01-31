#pragma once

#include "Action.h"
#include "Entities/Character.h"

class AttackAction : public Action {
public:
    AttackAction(Character &character, Character &other) :
        character(character),
        other(other) {}

    void execute() override;

    float getSpeed() override { return character.getSpeed(); }

private:
    Character &character;
    Character &other;
};