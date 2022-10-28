#include "Game.h"

Game::Game() : m_window(sf::VideoMode(Constants::GAME_WIDTH, Constants::GAME_HEIGHT), Constants::GAME_NAME, sf::Style::Titlebar | sf::Style::Close) {
    m_window.setFramerateLimit(60);

    m_entityManager = std::make_unique<EntityManager>();

    m_resourceManager = std::make_unique<ResourceManager>(Constants::GAME_DATA_DIR);
    m_resourceManager->loadResources();

    // Setup map
    m_tilemap = std::make_unique<TileMap>(m_resourceManager->getTexture("tilemap0"));
    const int map_w = 15;
    const int map_h = 7;
    int map_empty[map_w * map_h];
    for (int i = 0; i < map_w; i++) {
        for (int j = 0; j < map_h; j++) {
            map_empty[i + j * map_w] = (i == 0 || i == map_w - 1 || j == 0 || j == map_h - 1) ? 1 : 0;
        }
    }
    m_tilemap->loadFromArray(map_empty, map_w, map_h);
    m_tilemap->updateVertexArray();

    // Setup world camera
    m_worldView.reset(sf::FloatRect(0.f, 0.f, Constants::GAME_WIDTH, Constants::GAME_HEIGHT));
    m_worldView.zoom(0.5f);
    m_window.setView(m_worldView);

    m_text_test.setFont(*m_resourceManager->getFont("mono"));
    m_text_test.setCharacterSize(15);
    m_text_test.setFillColor(sf::Color::White);
    m_text_test.setPosition(10, 10);
    m_text_test.setString("Test test test!");

    m_entityManager->insertEntity(std::make_shared<Player>(0, *m_resourceManager));

    m_player = std::dynamic_pointer_cast<Player>(m_entityManager->getEntity(0));
    m_player->setGridPosition(map_w / 2, map_h / 2);
}

void Game::run() {
    while (m_window.isOpen()) {
        sf::Event event {};

        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    handleInput(event.key.code);
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
    m_worldView.setCenter(sf::Vector2f(m_player->getPosition().x + (Constants::GRID_SIZE / 2), m_player->getPosition().y + (Constants::GRID_SIZE / 2)));

    // Show testing stuff (std::format when?)
    snprintf(m_text_test_buff, sizeof(m_text_test_buff), "POS: [x=%.1f, y=%.1f] [gx=%d, gy=%d]\nENT: %zu\nMAP: %dx%d [V=%zu]",
             m_player->getPosition().x, m_player->getPosition().y,
             m_player->getGridPosition().x, m_player->getGridPosition().y,
             m_entityManager->count(),
             m_tilemap->getWidth(), m_tilemap->getHeight(), m_tilemap->getVertices());
    m_text_test.setString(m_text_test_buff);
}

void Game::processTurn() {

}

void Game::handleInput(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Escape:
            m_window.close();
            break;
        default:
            break;
    }
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