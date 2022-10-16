#include "Game.hpp"

#define GAME_NAME "Roguelike"
#define GAME_DATA_DIR "data"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 640

const int map[] = {
    0, 0, 0, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

Game::Game() : m_window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_NAME, sf::Style::Titlebar | sf::Style::Close) {
    m_window.setFramerateLimit(60);

    m_entityManager = std::make_unique<EntityManager>();

    m_resourceManager = std::make_unique<ResourceManager>(GAME_DATA_DIR);
    m_resourceManager->loadResources();

    // Setup map
    m_tilemap = std::make_unique<TileMap>(m_resourceManager->getTexture("tilemap0"));
    m_tilemap->loadFromArray(map, 8, 5);
    m_tilemap->updateVertexArray();

    // Setup world camera
    m_worldView.reset(sf::FloatRect(0.f, 0.f, GAME_WIDTH, GAME_HEIGHT));
    m_worldView.zoom(0.5f);
    m_window.setView(m_worldView);

    m_text_test.setFont(*m_resourceManager->getFont("default"));
    m_text_test.setCharacterSize(16);
    m_text_test.setFillColor(sf::Color::White);
    m_text_test.setPosition(10, 10);
    m_text_test.setString("Test test test!");

    m_entityManager->insertEntity(std::make_shared<Player>(0, *m_resourceManager));
}

void Game::run() {
    while (m_window.isOpen()) {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                default:
                    break;
            }
        }

        this->update();
        this->draw();
        m_window.display();
    }
}

void Game::update() {
    // Center camera on player
    auto player = m_entityManager->getEntity(0);
    m_worldView.setCenter(sf::Vector2f(player->getPosition().x + 16.f, player->getPosition().y + 16.f));
}

void Game::processTurn() {

}

void Game::draw() {
    m_window.clear();

    // WORLD
    m_window.setView(m_worldView);
    // Map
    m_window.draw(*m_tilemap);
    // Entities
    for (auto const& [id, entity] : m_entityManager->getAllEntities()) {
        m_window.draw(*entity);
    }

    // GUI
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_text_test);
}