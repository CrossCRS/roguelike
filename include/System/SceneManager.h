#pragma once

#include "Scenes/Scene.h"

#include <memory>
#include <unordered_map>

class SceneManager {
public:
	SceneManager();

	void handleInput(sf::Keyboard::Key key);
	void update(float delta, float elapsed);
	void draw();

	void addScene(unsigned int sceneId, std::shared_ptr<Scene> scene);
	void switchScene(unsigned int sceneId);

private:
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
	unsigned int sceneCount;
	std::shared_ptr<Scene> currentScene;
};