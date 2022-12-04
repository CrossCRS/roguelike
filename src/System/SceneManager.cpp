#include "System/SceneManager.h"

#include <magic_enum.hpp>
#include <spdlog/spdlog.h>

void SceneManager::handleInput(sf::Keyboard::Key key) {
	if (currentScene) currentScene->handleInput(key);
}

void SceneManager::update(float delta, float elapsed) {
	if (currentScene) currentScene->update(delta, elapsed);
}

void SceneManager::draw() {
	if (currentScene) currentScene->draw();
}

void SceneManager::addScene(SceneIndex sceneId, std::unique_ptr<Scene> scene) {
	spdlog::debug("Adding scene {}", magic_enum::enum_name(sceneId));
	scenes.emplace(sceneId, std::move(scene)).first->second->onCreate();
}

void SceneManager::switchScene(SceneIndex sceneId) {
	spdlog::debug("Switching to scene {}", magic_enum::enum_name(sceneId));

	if (!scenes.contains(sceneId)) {
		const auto message = "Scene '" + std::string(magic_enum::enum_name(sceneId)) + "' does not exist";
		spdlog::error(message);
		throw std::invalid_argument(message);
	}

	if (currentScene) currentScene->onUnload(); // Unload current scene
	currentScene = (scenes.find(sceneId)->second).get(); // Change current scene
	currentScene->onLoad(); // Load new scene
}
