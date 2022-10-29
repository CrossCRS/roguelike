#include "System/SceneManager.h"

void SceneManager::handleInput(sf::Keyboard::Key key) {
	if (currentScene) currentScene->handleInput(key);
}

void SceneManager::update(float delta, float elapsed) {
	if (currentScene) currentScene->update(delta, elapsed);
}

void SceneManager::draw() {
	if (currentScene) currentScene->draw();
}

void SceneManager::addScene(unsigned int sceneId, std::shared_ptr<Scene> scene) {
	scenes.emplace(sceneId, std::move(scene)).first->second->onCreate();
}

void SceneManager::switchScene(unsigned int sceneId) {
	auto it = scenes.find(sceneId);

	if (it == scenes.end()) {
		throw std::invalid_argument("Scene '" + std::to_string(sceneId) + "' does not exist");
	}

	if (currentScene) currentScene->onUnload(); // Unload current scene
	currentScene = it->second; // Change current scene
	currentScene->onLoad(); // Load new scene
}
