#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow m_window;

        sf::Font m_font_default;
        sf::Text m_text_test;

        void update();
        void draw();
};