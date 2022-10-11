#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

#include "ResourceManager.hpp"
#include "Player.hpp"

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow m_window;
        sf::View m_worldView;

        ResourceManager m_resourceManager;
        
        sf::Text m_text_test;
        std::unique_ptr<Player> m_player;

        void update();
        void draw();
};