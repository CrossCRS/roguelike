#pragma once

#include "Scenes/Scene.h"

#include <spdlog/spdlog.h>
#include <memory>
#include <unordered_map>

class SceneManager {
public:
	SceneManager() : currentScene(nullptr) {}

	void handleInput(sf::Keyboard::Key key);
	void update(float delta, float elapsed);
	void draw();

	void addScene(unsigned int sceneId, std::unique_ptr<Scene> scene);
	void switchScene(unsigned int sceneId);

private:
	std::unordered_map<unsigned int, std::unique_ptr<Scene>> scenes;
	Scene *currentScene;
};