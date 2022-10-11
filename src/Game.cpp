#include "Game.hpp"

#define GAME_NAME "Roguelike"
#define GAME_DATA_DIR "data"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 640

Game::Game() : m_window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_NAME, sf::Style::Titlebar | sf::Style::Close),
            m_resourceManager(GAME_DATA_DIR) {
    m_window.setFramerateLimit(60);

    m_resourceManager.loadResources();

    // Setup world camera
    m_worldView.reset(sf::FloatRect(0.f, 0.f, GAME_WIDTH, GAME_HEIGHT));
    m_worldView.zoom(0.5f);
    m_window.setView(m_worldView);

    m_text_test.setFont(*m_resourceManager.getFont("default"));
    m_text_test.setCharacterSize(24);
    m_text_test.setFillColor(sf::Color::White);
    m_text_test.setPosition(10, 10);
    m_text_test.setString("Test test test!");

    m_player = std::make_unique<Player>(0, m_resourceManager);
    m_player->setPosition(0, 0);

    // Center camera on player
    m_worldView.setCenter(sf::Vector2f(m_player->getPosition().x + 16.f, m_player->getPosition().y + 16.f));
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
    m_window.clear(sf::Color(64, 64, 64));

    // WORLD
    m_window.setView(m_worldView);
    m_window.draw(*m_player);

    // GUI
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_text_test);
}