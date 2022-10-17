#pragma once
#include "Entities/Player.hpp"
#include "System/EntityManager.hpp"
#include "System/ResourceManager.hpp"
#include "TileMap.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow m_window;
        sf::View m_worldView;

        std::unique_ptr<EntityManager> m_entityManager;
        std::unique_ptr<ResourceManager> m_resourceManager;
        
        std::unique_ptr<TileMap> m_tilemap;

        std::shared_ptr<Player> m_player;

        char m_text_test_buff[255];
        sf::Text m_text_test;

        void update();
        void processTurn();
        void handleInput(sf::Keyboard::Key key);
        void draw();
};