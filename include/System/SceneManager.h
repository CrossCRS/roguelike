#pragma once

#include "Scenes/Scene.h"

#include <memory>
#include <unordered_map>

class SceneManager {
public:
	SceneManager() : currentScene(nullptr) {}

	void handleInput(sf::Keyboard::Key key);
	void update(float delta, float elapsed);
	void draw();

	void addScene(SceneIndex sceneId, std::unique_ptr<Scene> scene);
	void switchScene(SceneIndex sceneId);

private:
	std::unordered_map<SceneIndex, std::unique_ptr<Scene>> scenes;
	Scene *currentScene;
};