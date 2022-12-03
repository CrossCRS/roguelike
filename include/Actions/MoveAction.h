#pragma once

#include "Action.h"
#include "Entities/Character.h"

#include <SFML/System/Vector2.hpp>

class MoveAction : public Action {
public:
    MoveAction(Character &character, sf::Vector2i moveDirection) :
        character(character),
        moveDirection(moveDirection) {}

    void execute() override;

    float getSpeed() override { return character.getSpeed(); }

private:
    Character &character;
    sf::Vector2i moveDirection;
};