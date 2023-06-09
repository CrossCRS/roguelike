#include "System/Resources/ResourceManager.h"

#include "Constants.h"
#include "System/Factories/ItemFactory.h"
#include "System/Factories/MonsterFactory.h"

#include <spdlog/spdlog.h>

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

    // Monsters
    spdlog::debug("Loading monster definitions");
    loaded = MonsterFactory::loadDefinitions(std::string(Constants::GAME_DATA_DIR) + "/monsters/");
    spdlog::info("Loaded {} monster definitions", loaded);

    // Items
    spdlog::debug("Loading item definitions");
    loaded = ItemFactory::loadDefinitions(std::string(Constants::GAME_DATA_DIR) + "/items/");
    spdlog::info("Loaded {} item definitions", loaded);
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string &name) const {
    return fontStore->getResource(name);
}


std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string &name) const {
    return textureStore->getResource(name);
}