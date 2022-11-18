#pragma once

#include "Action.h"
#include "Entities/Character.h"
#include "Map/TileMap.h"

#include <SFML/Graphics.hpp>

class MoveAction : public Action {
public:
    MoveAction(std::shared_ptr<Character> character, sf::Vector2i moveDirection) :
        character(std::move(character)),
        moveDirection(moveDirection) {}

    void execute() override;

    std::shared_ptr<Character> getPerformer() override { return character; }

private:
    std::shared_ptr<Character> character;
    sf::Vector2i moveDirection;
};