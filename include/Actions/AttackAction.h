#pragma once

#include "Action.h"
#include "Entities/Character.h"

#include <random>

class AttackAction : public Action {
public:
    AttackAction(Character &character, Character &other) :
        character(character),
        other(other),
        rd(), gen(rd()), distribution(0, 1) {}

    void execute() override;

    float getSpeed() override { return character.getSpeed(); }

private:
    Character &character;
    Character &other;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> distribution;
};