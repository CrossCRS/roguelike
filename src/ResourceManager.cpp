#include "ResourceManager.hpp"

ResourceManager::ResourceManager(const std::string& dataDirectory) : m_dataDir(dataDirectory) {

}

void ResourceManager::loadResources() {
    printf("[ResourceManager] Loading fonts\n");
    this->loadFonts();
}

bool ResourceManager::addFont(const std::string& name, const std::string& path) {
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

    if (font->loadFromFile(m_dataDir + "/fonts/" + path)) {
        m_fonts.emplace(name, std::move(font));
        printf("[ResourceManager] Loaded font '%s' as '%s'\n", path.c_str(), name.c_str());
        return true;
    } else {
        printf("[ResourceManager] Couldn't load font '%s'\n", path.c_str());
        return false;
    }
}

void ResourceManager::loadFonts() {
    this->addFont("default", "alagard_by_pix3m.ttf");
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = m_fonts.find(name);

    if (it == m_fonts.end()) {
        throw std::invalid_argument("Font '" + name + "' is not loaded");
    }

    return *(it->second);
}