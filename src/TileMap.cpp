#include "TileMap.hpp"

TileMap::TileMap(std::shared_ptr<sf::Texture> tileset) : m_tileset(tileset) {
    
}

// Load a simple map from int array (for testing)
void TileMap::loadFromArray(const int* map, uint width, uint height) {
    this->width = width;
    this->height = height;

    m_tiles.resize(width * height);

    for (uint i = 0; i < width; ++i) {
        for (uint j = 0; j < height; ++j) {
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

            m_tiles[i + j * width] = std::move(tile);
        }
    }
}

void TileMap::updateVertexArray() {
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    for (uint i = 0; i < width; ++i) {
        for (uint j = 0; j < height; ++j) {
            if (m_tiles[i + j * width] == nullptr) {
                continue;
            }

            // Get texture position
            uint tu = m_tiles[i + j * width]->getTextureId() % (m_tileset->getSize().x / 32);
            uint tv = m_tiles[i + j * width]->getTextureId() / (m_tileset->getSize().x / 32);

            sf::Vertex* triangle = &m_vertices[(i + j * width) * 6];

            triangle[0].position = sf::Vector2f(i * 32, j * 32);
            triangle[1].position = sf::Vector2f((i + 1) * 32, j * 32);
            triangle[2].position = sf::Vector2f((i + 1) * 32, (j + 1) * 32);
            triangle[3].position = sf::Vector2f(i * 32, j * 32);
            triangle[4].position = sf::Vector2f(i * 32, (j + 1) * 32);
            triangle[5].position = sf::Vector2f((i + 1) * 32, (j + 1) * 32);

            triangle[0].texCoords = sf::Vector2f(tu * 32, tv * 32);
            triangle[1].texCoords = sf::Vector2f((tu + 1) * 32, tv * 32);
            triangle[2].texCoords = sf::Vector2f((tu + 1) * 32, (tv + 1) * 32);
            triangle[3].texCoords = sf::Vector2f(tu * 32, tv * 32);
            triangle[4].texCoords = sf::Vector2f(tu * 32, (tv + 1) * 32);
            triangle[5].texCoords = sf::Vector2f((tu + 1) * 32, (tv + 1) * 32);
        }
    }
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = m_tileset.get();
    target.draw(m_vertices, states);
}