#pragma once

#include "Scene.h"
#include "Actions/MoveAction.h"
#include "Entities/Player.h"
#include "Map/TileMap.h"
#include "System/ResourceManager.h"
#include "System/SceneManager.h"
#include "Actions/ActionQueue.h"

#include <SFML/Graphics.hpp>
#include <fmt/core.h>

class GameScene : public Scene {
public:
	GameScene(SceneManager &/*sceneManager*/, ResourceManager &resourceManager, sf::RenderWindow &window) :
		/*sceneManager(sceneManager),*/
		resourceManager(resourceManager),
		window(window),
        turnCount(0) {}

	void onLoad() override;
	void onUnload() override;

    void processTurn();

	void handleInput(sf::Keyboard::Key key) override;
	void update(float delta, float elapsed) override;
	void draw() override;

private:
	//SceneManager &sceneManager;
	ResourceManager &resourceManager;
	sf::RenderWindow &window;

	sf::View worldView;

    std::unique_ptr<ActionQueue> actionQueue;
	std::unique_ptr<TileMap> tilemap;
	std::shared_ptr<Player> player;

    unsigned long turnCount;
	
	sf::Text text_debug;
};