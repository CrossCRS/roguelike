#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class ResourceManager {
    public:
        ResourceManager(const std::string& dataDirectory);

        void loadResources();

        std::shared_ptr<sf::Font> getFont(const std::string& name);
        std::shared_ptr<sf::Texture> getTexture(const std::string& name);

    private:
        const std::string m_dataDir;

        void loadFonts();
        void loadTextures();
        
        bool addFont(const std::string& name, const std::string& path);
        bool addTexture(const std::string& name, const std::string& path);

        std::unordered_map<std::string, std::shared_ptr<sf::Font>> m_fonts;
        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
};