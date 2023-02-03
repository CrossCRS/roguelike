#pragma once

#include "Scene.h"
#include "Actions/ActionQueue.h"
#include "GUI/GUICharacterScreen.h"
#include "GUI/GUIInventory.h"
#include "Map/World.h"

#include <SFML/Graphics.hpp>

class SceneManager;
class ResourceManager;

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
	std::unique_ptr<World> world;

    unsigned long turnCount;
	
	sf::Text text_debug;

	// Simple UI :(
	std::unique_ptr<GUIInventory> guiInventory;
    std::unique_ptr<GUICharacterScreen> guiCharacter;
};