#pragma once

#include "System/Factories/MonsterFactory.h"
#include "System/Resources/ResourceStore.h"

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

class ResourceManager {
public:
    explicit ResourceManager(std::string _dataDir);

    void loadResources();

    std::shared_ptr<sf::Font> getFont(const std::string &name) const;
    std::shared_ptr<sf::Texture> getTexture(const std::string &name) const;

private:
    const std::string dataDir;

    std::unique_ptr<ResourceStore<sf::Font>> fontStore;
    std::unique_ptr<ResourceStore<sf::Texture>> textureStore;
};