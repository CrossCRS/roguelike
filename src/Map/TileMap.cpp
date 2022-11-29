#include "Map/TileMap.h"

using json = nlohmann::json;

// Load a simple map from char array (for testing)
void TileMap::loadFromArray(const char *map, unsigned int _width, unsigned int _height) {
    spdlog::debug("Loading {}x{} tilemap from array", _width, _height);
    this->width = _width;
    this->height = _height;

    tiles.clear();
    tiles.resize(width * height);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            std::unique_ptr<BaseTile> tile = nullptr;

            switch (map[i + j * width]) {
                case '-': // Floors
                    tile = std::make_unique<FloorTile>(0);
                    break;
                case '#': // Walls
                    tile = std::make_unique<WallTile>(22);
                    break;
                case 'D': // Doors
                    tile = std::make_unique<DoorTile>(28, 29);
                    break;
                default:
                    break;
            }

            tiles[i + j * width] = std::move(tile);
        }
    }
}

void TileMap::loadFromFile(const std::string &mapName) {
    const auto path = "data/maps/" + mapName + ".json";

    spdlog::debug("Loading tilemap from {}", path);
    std::ifstream mapConfig(path);

    if (!mapConfig.good()) {
        const auto message = "Couldn't load tilemap from " + path;
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    json configData = json::parse(mapConfig);

    unsigned int mapWidth = configData["width"].get<unsigned int>();
    unsigned int mapHeight = configData["height"].get<unsigned int>();

    std::ifstream mapTiles("data/maps/" + configData["tiles"].get<std::string>());

    if (!mapTiles.good()) {
        const auto message = "Couldn't load map data file";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    // Remove all new lines
    std::string map((std::istreambuf_iterator<char>(mapTiles)), std::istreambuf_iterator<char>());
    map.erase(std::remove(map.begin(), map.end(), '\n'), map.cend());

    loadFromArray(map.c_str(), mapWidth, mapHeight);
    setPlayerSpawnPoint({ configData["spawn"]["x"].get<int>(), configData["spawn"]["y"].get<int>() });
}

void TileMap::updateVertexArray() {
    vertices.setPrimitiveType(sf::Triangles);
    vertices.resize(width * height * 6);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            if (tiles[i + j * width] == nullptr) {
                continue;
            }

            // Get texture position
            float tu = static_cast<float>(tiles[i + j * width]->getTextureId() %
                                          (tileset->getSize().x / Constants::GRID_SIZE));
            float tv = static_cast<float>(tiles[i + j * width]->getTextureId() /
                                          (tileset->getSize().x / Constants::GRID_SIZE));

            sf::Vertex *triangle = &vertices[(i + j * width) * 6];

            triangle[0].position = sf::Vector2f(static_cast<float>(i * Constants::GRID_SIZE), static_cast<float>(j * Constants::GRID_SIZE));
            triangle[1].position = sf::Vector2f(static_cast<float>((i + 1) * Constants::GRID_SIZE),
                                                static_cast<float>(j * Constants::GRID_SIZE));
            triangle[2].position = sf::Vector2f(static_cast<float>((i + 1) * Constants::GRID_SIZE),
                                                static_cast<float>((j + 1) * Constants::GRID_SIZE));
            triangle[3].position = sf::Vector2f(static_cast<float>(i * Constants::GRID_SIZE), static_cast<float>(j * Constants::GRID_SIZE));
            triangle[4].position = sf::Vector2f(static_cast<float>(i * Constants::GRID_SIZE),
                                                static_cast<float>((j + 1) * Constants::GRID_SIZE));
            triangle[5].position = sf::Vector2f(static_cast<float>((i + 1) * Constants::GRID_SIZE),
                                                static_cast<float>((j + 1) * Constants::GRID_SIZE));

            triangle[0].texCoords = sf::Vector2f(tu * Constants::GRID_SIZE, tv * Constants::GRID_SIZE);
            triangle[1].texCoords = sf::Vector2f((tu + 1) * Constants::GRID_SIZE, tv * Constants::GRID_SIZE);
            triangle[2].texCoords = sf::Vector2f((tu + 1) * Constants::GRID_SIZE, (tv + 1) * Constants::GRID_SIZE);
            triangle[3].texCoords = sf::Vector2f(tu * Constants::GRID_SIZE, tv * Constants::GRID_SIZE);
            triangle[4].texCoords = sf::Vector2f(tu * Constants::GRID_SIZE, (tv + 1) * Constants::GRID_SIZE);
            triangle[5].texCoords = sf::Vector2f((tu + 1) * Constants::GRID_SIZE, (tv + 1) * Constants::GRID_SIZE);
        }
    }
}

void TileMap::setTileset(std::shared_ptr<sf::Texture> _tileset) {
    tileset = std::move(_tileset);
}


BaseTile &TileMap::getTile(const sf::Vector2i &pos) const {
    if (pos.x < 0 || pos.y < 0 || static_cast<unsigned int>(pos.x) > width - 1 || static_cast<unsigned int>(pos.y) > height - 1) {
        const auto message = "Map position out of bounds";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }
    if (tiles[pos.x + pos.y * width] == nullptr) {
        const auto message = "Map position is empty";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }
    return *tiles[pos.x + pos.y * width];
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Draw the map
    states.transform *= getTransform();
    states.texture = tileset.get();
    target.draw(vertices, states);
}

void TileMap::setPlayerSpawnPoint(const sf::Vector2i &spawnPoint) {
    spdlog::debug("Setting player spawn point to [{}, {}]", spawnPoint.x, spawnPoint.y);
    playerSpawnPoint = spawnPoint;
}