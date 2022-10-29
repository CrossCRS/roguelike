#pragma once

#include "Actions/MoveAction.h"
#include "Entities/Player.h"
#include "Scene.h"
#include "System/ResourceManager.h"
#include "System/SceneManager.h"
#include "TileMap.h"

#include <SFML/Graphics.hpp>

class GameScene : public Scene {
public:
	GameScene(SceneManager &sceneManager, ResourceManager &resourceManager, sf::RenderWindow &window);

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