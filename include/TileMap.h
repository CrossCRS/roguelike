#pragma once

#include "Constants.h"
#include "Tile.h"

#include <SFML/Graphics.hpp>
#include <memory>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    explicit TileMap(std::shared_ptr<sf::Texture> tileset);

    void loadFromArray(const int *map, unsigned int _width, unsigned int _height);

    void updateVertexArray();

    inline unsigned int getWidth() const { return width; }
    inline unsigned int getHeight() const { return height; }
    inline size_t getVertices() const { return m_vertices.getVertexCount(); }

private:
    unsigned int width;
    unsigned int height;
    sf::VertexArray m_vertices;
    std::shared_ptr<sf::Texture> m_tileset;
    std::vector<std::unique_ptr<Tile>> m_tiles;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};