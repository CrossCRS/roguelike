#pragma once
#include "Tile.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class TileMap : public sf::Drawable, public sf::Transformable {
    public:
        TileMap(std::shared_ptr<sf::Texture> tileset);
        void loadFromArray(const int* map, unsigned int _width, unsigned int _height);
        void updateVertexArray();
        unsigned int getWidth() const { return width; }
        unsigned int getHeight() const { return height; }
        size_t getVertices() const { return m_vertices.getVertexCount(); }

    private:
        unsigned int width;
        unsigned int height;
        sf::VertexArray m_vertices;
        std::shared_ptr<sf::Texture> m_tileset;
        std::vector<std::unique_ptr<Tile>> m_tiles;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};