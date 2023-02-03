#include "Scenes/GameScene.h"

#include "Constants.h"
#include "Actions/MoveAction.h"
#include "Entities/Player.h"
#include "System/Resources/ResourceManager.h"
#include "System/SceneManager.h"
#include "Map/TileMap.h"

#include <fmt/core.h>

void GameScene::onLoad() {
    // Setup action queue
    actionQueue = std::make_unique<ActionQueue>();

    // Setup world and map
    world = std::make_unique<World>(resourceManager);
    world->getMap().setTileset(resourceManager.getTexture("tilemap0"));
    world->getMap().loadFromFile("sample_map");
    world->getMap().updateVertexArray();

    // Setup world camera
    worldView.reset(sf::FloatRect(0.f, 0.f, Constants::GAME_WIDTH, Constants::GAME_HEIGHT));
    worldView.zoom(1.f);
    window.setView(worldView);

    text_debug.setFont(*resourceManager.getFont("mono"));
    text_debug.setCharacterSize(15);
    text_debug.setFillColor(sf::Color::White);
    text_debug.setPosition(10, 10);
    text_debug.setString("");

    world->spawnPlayer();

    guiInventory = std::make_unique<GUIInventory>(*world, world->getPlayer().getInventory());
    guiCharacter = std::make_unique<GUICharacterScreen>(*world, world->getPlayer());

    // Spawn some test monsters
    world->spawnMonster("rat", { 36, 2 });
    world->spawnMonster("rat", { 41, 5 });
    world->spawnMonster("rat", { 35, 3 });
    world->spawnMonster("rat", { 38, 6 });
    world->spawnMonster("goblin", { 23, 1 });

    // Spawn some test items
    world->spawnGroundItem("holy_bread", { 10, 4 });
    world->spawnGroundItem("holy_bread", { 10, 3 });
    world->spawnGroundItem("butter_knife", { 10, 2 });
}

void GameScene::onUnload() {}

void GameScene::processTurn() {
    // Process player turn
    if (actionQueue->processPlayerAction()) {
        // "Think" on every NPC and add its action
        for (const auto &[id, monster] : world->getMonsterManager().getAllEntities()) {
            actionQueue->addAction(monster->think());
        }

        // Process NPC turn
        actionQueue->processActions();

        // Update map vertices in case any texture changed
        world->getMap().updateVertexArray();

        turnCount++;
    }
}

void GameScene::handleInput(sf::Keyboard::Key key) {
    // TODO: Input manager?
    if (guiInventory->isOpened()) {
        guiInventory->handleInput(key);
        return;
    }
    if (guiCharacter->isOpened()) {
        guiCharacter->handleInput(key);
        return;
    }

    switch (key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        case sf::Keyboard::Up:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(world->getPlayer(), sf::Vector2i(0, -1)));
            break;
        case sf::Keyboard::Right:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(world->getPlayer(), sf::Vector2i(1, 0)));
            break;
        case sf::Keyboard::Down:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(world->getPlayer(), sf::Vector2i(0, 1)));
            break;
        case sf::Keyboard::Left:
            actionQueue->setPlayerAction(std::make_unique<MoveAction>(world->getPlayer(), sf::Vector2i(-1, 0)));
            break;
        case sf::Keyboard::I:
            guiInventory->open();
            break;
        case sf::Keyboard::C:
            guiCharacter->open();
            break;
        default:
            break;
    }

    processTurn();
}

#ifdef BREAD_DEBUG
void GameScene::update(float delta, float) {
#else
void GameScene::update(float, float) {
#endif
    Player &player = world->getPlayer();

    // Center camera on player
    worldView.setCenter(sf::Vector2f(player.getPosition().x + (Constants::GRID_SIZE / 2),
        player.getPosition().y + (Constants::GRID_SIZE / 2)));

    // Inventory
    guiInventory->update();
    guiCharacter->update();

    // Show testing stuff
#ifdef BREAD_DEBUG
    text_debug.setString(fmt::format("POS: [x={:.1f}, y={:.1f}] [gx={:d}, gy={:d}]\nMON: {:d}\nMAP: {:d}x{:d} [V={:d}]\nTIM: {:.3f}s\nTRN: {:d}",
        world->getPlayer().getPosition().x, world->getPlayer().getPosition().y,
        world->getPlayer().getGridPosition().x, world->getPlayer().getGridPosition().y,
        world->getMonsterManager().count(),
        world->getMap().getWidth(), world->getMap().getHeight(), world->getMap().getVerticesCount(),
        delta, turnCount));
#endif
}

void GameScene::draw() {
    window.clear();

    // WORLD
    window.setView(worldView);
    window.draw(*world);

    // GUI
    window.setView(window.getDefaultView());
    window.draw(text_debug);
    window.draw(*guiInventory);
    window.draw(*guiCharacter);
}