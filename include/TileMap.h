#pragma once

#include "Constants.h"
#include "Tile.h"

#include <SFML/Graphics.hpp>
#include <memory>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    explicit TileMap(std::shared_ptr<sf::Texture> tileset) : tileset(std::move(tileset)) {}

    void loadFromArray(const int *map, unsigned int _width, unsigned int _height);

    void updateVertexArray();

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
    size_t getVertices() const { return vertices.getVertexCount(); }

private:
    unsigned int width;
    unsigned int height;
    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> tileset;
    std::vector<std::unique_ptr<Tile>> tiles;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};