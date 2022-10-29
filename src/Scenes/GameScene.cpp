#include "Scenes/GameScene.h"

GameScene::GameScene(SceneManager &/*sceneManager*/, ResourceManager &resourceManager, sf::RenderWindow &window) :
	/*sceneManager(sceneManager),*/ resourceManager(resourceManager), window(window) {}

void GameScene::onLoad() {
    // Setup map
    tilemap = std::make_unique<TileMap>(resourceManager.getTexture("tilemap0"));
    constexpr int map_w = 15;
    constexpr int map_h = 7;
    int map_empty[map_w * map_h];
    for (int i = 0; i < map_w; i++) {
        for (int j = 0; j < map_h; j++) {
            map_empty[i + j * map_w] = (i == 0 || i == map_w - 1 || j == 0 || j == map_h - 1) ? 1 : 0;
        }
    }
    tilemap->loadFromArray(map_empty, map_w, map_h);
    tilemap->updateVertexArray();

    // Setup world camera
    worldView.reset(sf::FloatRect(0.f, 0.f, Constants::GAME_WIDTH, Constants::GAME_HEIGHT));
    worldView.zoom(0.5f);
    window.setView(worldView);

    text_test.setFont(*resourceManager.getFont("mono"));
    text_test.setCharacterSize(15);
    text_test.setFillColor(sf::Color::White);
    text_test.setPosition(10, 10);
    text_test.setString("Test test test!");

    tilemap->getEntityManager().insertEntity(std::make_shared<Player>(0, resourceManager, *tilemap));

    player = std::dynamic_pointer_cast<Player>(tilemap->getEntityManager().getEntity(0));
    player->setGridPosition(map_w / 2, map_h / 2);
}

void GameScene::onUnload() {
    tilemap.reset();
}

void GameScene::handleInput(sf::Keyboard::Key key) {
    // TODO: Action handler?
    switch (key) {
    case sf::Keyboard::Escape:
        window.close();
        break;
    case sf::Keyboard::Up:
        MoveAction(player, sf::Vector2i(0, -1)).execute();
        break;
    case sf::Keyboard::Right:
        MoveAction(player, sf::Vector2i(1, 0)).execute();
        break;
    case sf::Keyboard::Down:
        MoveAction(player, sf::Vector2i(0, 1)).execute();
        break;
    case sf::Keyboard::Left:
        MoveAction(player, sf::Vector2i(-1, 0)).execute();
        break;
    default:
        break;
    }
}

void GameScene::update(float delta, float) {
    // Center camera on player
    worldView.setCenter(sf::Vector2f(player->getPosition().x + (Constants::GRID_SIZE / 2),
        player->getPosition().y + (Constants::GRID_SIZE / 2)));

    // Show testing stuff (std::format when?)
    snprintf(text_test_buff, sizeof(text_test_buff),
        "POS: [x=%.1f, y=%.1f] [gx=%d, gy=%d]\nENT: %zu\nMAP: %dx%d [V=%zu]\nTIM: %.3f",
        player->getPosition().x, player->getPosition().y,
        player->getGridPosition().x, player->getGridPosition().y,
        tilemap->getEntityManager().count(),
        tilemap->getWidth(), tilemap->getHeight(), tilemap->getVertices(),
        delta);
    text_test.setString(text_test_buff);
}

void GameScene::draw() {
    window.clear();

    // WORLD
    window.setView(worldView);
    // Map
    window.draw(*tilemap);
    // Entities
    for (auto const& [id, entity] : tilemap->getEntityManager().getAllEntities()) {
        window.draw(*entity);
    }

    // GUI
    window.setView(window.getDefaultView());
    window.draw(text_test);
}