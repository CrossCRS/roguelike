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

	void addScene(Scene::Index sceneId, std::unique_ptr<Scene> scene);
	void switchScene(Scene::Index sceneId);

private:
	std::unordered_map<Scene::Index, std::unique_ptr<Scene>> scenes;
	Scene *currentScene;
};