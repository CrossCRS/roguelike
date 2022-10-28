#include "TileMap.h"

#include <utility>

TileMap::TileMap(std::shared_ptr<sf::Texture> tileset) : tileset(std::move(tileset)) {
    this->entityManager = std::make_unique<EntityManager>();
}

// Load a simple map from int array (for testing)
void TileMap::loadFromArray(const int *map, unsigned int _width, unsigned int _height) {
    this->width = _width;
    this->height = _height;

    tiles.resize(width * height);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            std::unique_ptr<Tile> tile = nullptr;

            switch (map[i + j * width]) {
                case 0:
                    tile = std::make_unique<Tile>(0);
                    break;
                case 1:
                    tile = std::make_unique<Tile>(22, true);
                    break;
                default:
                    break;
            }

            tiles[i + j * width] = std::move(tile);
        }
    }
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

Tile &TileMap::getTile(sf::Vector2i pos) const {
    return *tiles[pos.x + pos.y * width];
}

bool TileMap::canWalk(sf::Vector2i pos) const {
    return !getTile(pos).isImpenetrable();
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = tileset.get();
    target.draw(vertices, states);
}