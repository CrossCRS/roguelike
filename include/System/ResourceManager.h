#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    explicit ResourceManager(std::string dataDirectory) : dataDir(std::move(dataDirectory)) {}

    void loadResources();

    std::shared_ptr<sf::Font> getFont(const std::string &name) const;
    std::shared_ptr<sf::Texture> getTexture(const std::string &name) const;

private:
    const std::string dataDir;

    void loadFonts();
    void loadTextures();

    bool addFont(const std::string &name, const std::string &path);
    bool addTexture(const std::string &name, const std::string &path);

    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};