#pragma once

#include "Scene.h"
#include "Actions/MoveAction.h"
#include "Entities/Player.h"
#include "Map/TileMap.h"
#include "System/ResourceManager.h"
#include "System/SceneManager.h"

#include <SFML/Graphics.hpp>

class GameScene : public Scene {
public:
	GameScene(SceneManager &/*sceneManager*/, ResourceManager &resourceManager, sf::RenderWindow &window) :
		/*sceneManager(sceneManager),*/
		resourceManager(resourceManager),
		window(window) {}

	void onLoad() override;
	void onUnload() override;

	void handleInput(sf::Keyboard::Key key) override;
	void update(float delta, float elapsed) override;
	void draw() override;

private:
	//SceneManager &sceneManager;
	ResourceManager &resourceManager;
	sf::RenderWindow &window;

	sf::View worldView;

	std::unique_ptr<TileMap> tilemap;
	std::shared_ptr<Player> player;

	char text_test_buff[255];
	sf::Text text_test;
};