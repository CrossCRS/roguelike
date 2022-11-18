#include "Scenes/GameScene.h"

void GameScene::onLoad() {
    // Setup action queue
    actionQueue = std::make_unique<ActionQueue>();

    // Setup map
    tilemap = std::make_unique<TileMap>(resourceManager.getTexture("tilemap0"));
    tilemap->loadFromFile("sample_map");
    tilemap->updateVertexArray();

    // Setup world camera
    worldView.reset(sf::FloatRect(0.f, 0.f, Constants::GAME_WIDTH, Constants::GAME_HEIGHT));
    worldView.zoom(1.f);
    window.setView(worldView);

    text_debug.setFont(*resourceManager.getFont("mono"));
    text_debug.setCharacterSize(15);
    text_debug.setFillColor(sf::Color::White);
    text_debug.setPosition(10, 10);
    text_debug.setString("Test test test!");

    tilemap->getCharacterManager().insertEntity(std::make_shared<Player>(0, resourceManager.getTexture("player"), *tilemap));

    player = std::dynamic_pointer_cast<Player>(tilemap->getCharacterManager().getEntity(0));
    player->setGridPosition(tilemap->getPlayerSpawnPoint());
}

void GameScene::onUnload() {
    tilemap.reset();
}

void GameScene::processTurn() {
    // Process player turn
    if (actionQueue->processPlayerAction()) {
        // TODO: "Think" on all npc characters
        // Process npc characters' turn
        actionQueue->processActions();

        // Update map vertices in case any texture changed
        tilemap->updateVertexArray();

        turnCount++;
    }
}

void GameScene::handleInput(sf::Keyboard::Key key) {
    // TODO: Input manager?
    switch (key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        case sf::Keyboard::Up:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(player, sf::Vector2i(0, -1)));
            break;
        case sf::Keyboard::Right:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(player, sf::Vector2i(1, 0)));
            break;
        case sf::Keyboard::Down:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(player, sf::Vector2i(0, 1)));
            break;
        case sf::Keyboard::Left:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(player, sf::Vector2i(-1, 0)));
            break;
        default:
            break;
    }

    processTurn();
}

void GameScene::update(float delta, float) {
    // Center camera on player
    worldView.setCenter(sf::Vector2f(player->getPosition().x + (Constants::GRID_SIZE / 2),
        player->getPosition().y + (Constants::GRID_SIZE / 2)));

    // Show testing stuff
    text_debug.setString(fmt::format("POS: [x={:.1f}, y={:.1f}] [gx={:d}, gy={:d}]\nENT: {:d}\nMAP: {:d}x{:d} [V={:d}]\nTIM: {:.3f}s\nTRN: {:d}",
        player->getPosition().x, player->getPosition().y,
        player->getGridPosition().x, player->getGridPosition().y,
        tilemap->getCharacterManager().count(),
        tilemap->getWidth(), tilemap->getHeight(), tilemap->getVerticesCount(),
        delta, turnCount));
}

void GameScene::draw() {
    window.clear();

    // WORLD
    window.setView(worldView);
    window.draw(*tilemap);

    // GUI
    window.setView(window.getDefaultView());
    window.draw(text_debug);
}