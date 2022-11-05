#pragma once

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    explicit ResourceManager(std::string dataDirectory) : dataDir(std::move(dataDirectory)) {}

    void loadEssentialResources();
    void loadResources();

    std::shared_ptr<sf::Font> getFont(const std::string &name) const;
    std::shared_ptr<sf::Texture> getTexture(const std::string &name) const;

private:
    const std::string dataDir;

    void loadFonts();
    void loadTextures();

    bool addFont(const std::string &name, const std::string &filename);
    bool addTexture(const std::string &name, const std::string &path);

    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};