#include "Map/TileMap.h"

using json = nlohmann::json;

TileMap::TileMap(std::shared_ptr<sf::Texture> tileset) : tileset(std::move(tileset)) {
    this->entityManager = std::make_unique<EntityManager>();
}

// Load a simple map from char array (for testing)
void TileMap::loadFromArray(const char *map, unsigned int _width, unsigned int _height) {
    this->width = _width;
    this->height = _height;

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
    std::ifstream mapConfig("data/maps/" + mapName + ".json");

    if (!mapConfig.good()) {
        printf("Couldn't load %s.json\n", mapName.c_str());
        throw std::invalid_argument("Invalid map name");
    }

    json configData = json::parse(mapConfig);

    unsigned int mapWidth = configData["width"].get<unsigned int>();
    unsigned int mapHeight = configData["height"].get<unsigned int>();
    std::ifstream mapTiles("data/maps/" + configData["tiles"].get<std::string>());

    if (!mapTiles.good()) {
        printf("Couldn't load map data file\n");
        throw std::invalid_argument("Couldn't load map data file");
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

BaseTile &TileMap::getTile(sf::Vector2i pos) const {
    if (pos.x < 0 || pos.y < 0 || static_cast<unsigned int>(pos.x) > width - 1 || static_cast<unsigned int>(pos.y) > height - 1) {
        throw std::invalid_argument("Map position out of bounds");
    }
    if (tiles[pos.x + pos.y * width] == nullptr) {
        throw std::invalid_argument("Map position is empty");
    }
    return *tiles[pos.x + pos.y * width];
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Draw the map
    states.transform *= getTransform();
    states.texture = tileset.get();
    target.draw(vertices, states);

    // Draw entities
    for (auto const &element : entityManager->getAllEntities()) {
        target.draw(*element.second);
    }
}

void TileMap::setPlayerSpawnPoint(const sf::Vector2i &spawnPoint) {
    playerSpawnPoint = spawnPoint;
}