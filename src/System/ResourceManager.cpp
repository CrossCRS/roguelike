#include "System/ResourceManager.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

void ResourceManager::loadEssentialResources() {
    spdlog::debug("Loading essential resources");
    this->loadFonts();
    this->addTexture("splash_logo", dataDir + "/textures/splash_logo.png");
}

// TODO: Templates?
void ResourceManager::loadResources() {
    spdlog::debug("Loading resources");
    this->loadTextures();
    spdlog::info("Loaded {} textures, {} fonts", textures.size(), fonts.size());
}

// FONTS
bool ResourceManager::addFont(const std::string &name, const std::string &filename) {
    if (fonts.contains(name)) return false;

    auto font = std::make_shared<sf::Font>();

    if (font->loadFromFile(dataDir + "/fonts/" + filename)) {
        fonts.emplace(name, std::move(font));
        spdlog::debug("Loaded font {} as {}", filename, name);
        return true;
    } else {
        spdlog::error("Couldn't load font {}", filename);
        return false;
    }
}

void ResourceManager::loadFonts() {
    std::ifstream fontsConfig(dataDir + "/fonts/fonts.json");

    if (!fontsConfig.good()) {
        spdlog::error("Couldn't load fonts.json");
        return;
    }

    json data = json::parse(fontsConfig);

    for (auto &fontEntry: data) {
        this->addFont(fontEntry["name"].get<std::string>(), fontEntry["filename"].get<std::string>());
    }
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string &name) const {
    if (!fonts.contains(name)) {
        const auto message = "Font '" + name + "' is not loaded";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    return fonts.find(name)->second;
}

// TEXTURES
bool ResourceManager::addTexture(const std::string &name, const std::string &path) {
    if (textures.contains(name)) return false;

    auto texture = std::make_shared<sf::Texture>();

    if (texture->loadFromFile(path)) {
        textures.emplace(name, std::move(texture));
        spdlog::debug("Loaded texture {} as {}", path, name);
        return true;
    } else {
        spdlog::error("Couldn't load texture {}", path);
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
    if (!textures.contains(name)) {
        const auto message = "Texture '" + name + "' is not loaded";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    return textures.find(name)->second;
}