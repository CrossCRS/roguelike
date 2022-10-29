#include "System/ResourceManager.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

void ResourceManager::loadEssentialResources() {
    printf("[ResourceManager] Loading fonts\n");
    this->loadFonts();
    printf("[ResourceManager] Loaded %lu fonts\n", fonts.size());
    this->addTexture("splash_logo", dataDir + "/textures/splash_logo.png");
}

// TODO: Templates?
void ResourceManager::loadResources() {
    printf("[ResourceManager] Loading textures\n");
    this->loadTextures();
    printf("[ResourceManager] Loaded %lu textures\n", textures.size());
}

// FONTS
bool ResourceManager::addFont(const std::string &name, const std::string &filename) {
    auto font = std::make_shared<sf::Font>();

    if (fonts.find(name) != fonts.end()) {
        return false;
    }

    if (font->loadFromFile(dataDir + "/fonts/" + filename)) {
        fonts.emplace(name, std::move(font));
        printf("[ResourceManager] Loaded font '%s' as '%s'\n", filename.c_str(), name.c_str());
        return true;
    } else {
        printf("[ResourceManager] Couldn't load font '%s'\n", filename.c_str());
        return false;
    }
}

void ResourceManager::loadFonts() {
    std::ifstream fontsConfig(dataDir + "/fonts/fonts.json");

    if (!fontsConfig.good()) {
        printf("[ResourceManager] Couldn't load fonts.json\n");
        return;
    }

    json data = json::parse(fontsConfig);

    for (auto &fontEntry: data) {
        this->addFont(fontEntry["name"].get<std::string>(), fontEntry["filename"].get<std::string>());
    }
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string &name) const {
    auto it = fonts.find(name);

    if (it == fonts.end()) {
        throw std::invalid_argument("Font '" + name + "' is not loaded");
    }

    return it->second;
}

// TEXTURES
bool ResourceManager::addTexture(const std::string &name, const std::string &path) {
    auto texture = std::make_shared<sf::Texture>();

    if (textures.find(name) != textures.end()) {
        return false;
    }

    if (texture->loadFromFile(path)) {
        textures.emplace(name, std::move(texture));
        printf("[ResourceManager] Loaded texture '%s' as '%s'\n", path.c_str(), name.c_str());
        return true;
    } else {
        printf("[ResourceManager] Couldn't load texture '%s'\n", path.c_str());
        return false;
    }
}

void ResourceManager::loadTextures() {
    for (const auto &dir_entry: fs::recursive_directory_iterator(dataDir + "/textures/")) {
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".png") {
            const auto &path = dir_entry.path();
            this->addTexture(path.filename().replace_extension("").string(), path.string());
        }
    }
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string &name) const {
    auto it = textures.find(name);

    if (it == textures.end()) {
        throw std::invalid_argument("Texture '" + name + "' is not loaded");
    }

    return it->second;
}