#include "System/ResourceManager.hpp"

namespace fs = std::filesystem;

// TODO: Templates?
ResourceManager::ResourceManager(const std::string& dataDirectory) : m_dataDir(dataDirectory) {

}

void ResourceManager::loadResources() {
    printf("[ResourceManager] Loading fonts\n");
    this->loadFonts();
    printf("[ResourceManager] Loaded %lu fonts\n", m_fonts.size());
    printf("[ResourceManager] Loading textures\n");
    this->loadTextures();
    printf("[ResourceManager] Loaded %lu textures\n", m_textures.size());
}

// FONTS
bool ResourceManager::addFont(const std::string& name, const std::string& filename) {
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

    if (font->loadFromFile(m_dataDir + "/fonts/" + filename)) {
        m_fonts.emplace(name, std::move(font));
        printf("[ResourceManager] Loaded font '%s' as '%s'\n", filename.c_str(), name.c_str());
        return true;
    } else {
        printf("[ResourceManager] Couldn't load font '%s'\n", filename.c_str());
        return false;
    }
}

void ResourceManager::loadFonts() {
    this->addFont("default", "alagard_by_pix3m.ttf");
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string& name) {
    auto it = m_fonts.find(name);

    if (it == m_fonts.end()) {
        throw std::invalid_argument("Font '" + name + "' is not loaded");
    }

    return it->second;
}

// TEXTURES
bool ResourceManager::addTexture(const std::string& name, const std::string& path) {
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

    if (texture->loadFromFile(path)) {
        m_textures.emplace(name, std::move(texture));
        printf("[ResourceManager] Loaded texture '%s' as '%s'\n", path.c_str(), name.c_str());
        return true;
    } else {
        printf("[ResourceManager] Couldn't load texture '%s'\n", path.c_str());
        return false;
    }
}

void ResourceManager::loadTextures() {
    for (const auto& dir_entry : fs::recursive_directory_iterator(m_dataDir + "/textures/")) {
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".png") {
            auto path = dir_entry.path();
            this->addTexture(path.filename().replace_extension("").u8string(), path.u8string());
        }
    }
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string& name) {
    auto it = m_textures.find(name);

    if (it == m_textures.end()) {
        throw std::invalid_argument("Texture '" + name + "' is not loaded");
    }

    return it->second;
}