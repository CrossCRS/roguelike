#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

#include "EntityManager.hpp"
#include "ResourceManager.hpp"
#include "Player.hpp"

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow m_window;
        sf::View m_worldView;

        EntityManager m_entityManager;
        ResourceManager m_resourceManager;
        
        sf::Text m_text_test;

        void update();
        void draw();
};