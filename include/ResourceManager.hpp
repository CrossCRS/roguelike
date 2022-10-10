#pragma once
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager {
    public:
        ResourceManager(const std::string& dataDirectory);

        void loadResources();

        sf::Font& getFont(const std::string& name);

    private:
        std::string m_dataDir;

        void loadFonts();
        
        bool addFont(const std::string& name, const std::string& path);

        std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
};