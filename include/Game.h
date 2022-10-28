#pragma once

#include "Actions/MoveAction.h"
#include "Constants.h"
#include "Entities/Player.h"
#include "System/EntityManager.h"
#include "System/ResourceManager.h"
#include "TileMap.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
public:
    Game();

    void run();

private:
    sf::RenderWindow window;
    sf::View worldView;

    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<ResourceManager> resourceManager;

    std::unique_ptr<TileMap> tilemap;

    std::shared_ptr<Player> player;

    char text_test_buff[255];
    sf::Text text_test;

    void update();

    void processTurn();

    void handleInput(sf::Keyboard::Key key);

    void draw();
};