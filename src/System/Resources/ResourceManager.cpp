#include "System/Resources/ResourceManager.h"

ResourceManager::ResourceManager(std::string _dataDir) : dataDir(std::move(_dataDir)) {
    fontStore = std::make_unique<ResourceStore<sf::Font>>(dataDir + "/fonts/", "fonts.json");
    textureStore = std::make_unique<ResourceStore<sf::Texture>>(dataDir + "/textures/", "textures.json");
}

void ResourceManager::loadResources() {
    spdlog::debug("Loading resources");

    size_t loaded = 0;
    loaded += fontStore->loadResources();
    loaded += textureStore->loadResources();

    spdlog::info("Loaded {} resources", loaded);
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string &name) const {
    return fontStore->getResource(name);
}


std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string &name) const {
    return textureStore->getResource(name);
}