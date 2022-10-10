#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

#include "ResourceManager.hpp"

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow m_window;

        ResourceManager m_resourceManager;
        
        sf::Text m_text_test;

        void update();
        void draw();
};