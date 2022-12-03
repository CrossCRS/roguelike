#pragma once

#include "Scene.h"

#include <atomic>
#include <thread>
#include <SFML/Graphics.hpp>

class SceneManager;
class ResourceManager;

class SplashScene : public Scene {
public:
	SplashScene(SceneManager &sceneManager, ResourceManager &resourceManager, sf::RenderWindow &window);

	void onLoad() override;

	void handleInput(sf::Keyboard::Key key) override;
	void update(float delta, float elapsed) override;
	void draw() override;

private:
	SceneManager &sceneManager;
	ResourceManager &resourceManager;
	sf::RenderWindow &window;

	void centerText(sf::Text &text);

	void loadResourcesThreadFunc();
	std::thread loadResourcesThread;
	std::atomic_bool loadResourcesThreadFinished;

	bool loaded;
	
	sf::Text text_splash;
	sf::Text text_gamename;
    sf::Text text_copy;
	sf::Sprite splash_logo;
};