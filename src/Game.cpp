#include "Game.hpp"

#define GAME_NAME "Roguelike"
#define GAME_DATA_DIR "data"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 640

Game::Game() : m_window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_NAME, sf::Style::Titlebar | sf::Style::Close), m_resourceManager(GAME_DATA_DIR) {
    m_window.setFramerateLimit(60);

    m_resourceManager.loadResources();

    m_text_test.setFont(m_resourceManager.getFont("default"));
    m_text_test.setCharacterSize(24);
    m_text_test.setFillColor(sf::Color::White);
    m_text_test.setPosition(100, 100);
    m_text_test.setString("Test test test!");
}

void Game::run() {
    while (m_window.isOpen()) {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        this->update();
        this->draw();
        m_window.display();
    }
}

void Game::update() {

}

void Game::draw() {
    m_window.clear();
    m_window.draw(m_text_test);
}