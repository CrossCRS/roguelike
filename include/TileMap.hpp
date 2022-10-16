#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.hpp"

#include <memory>

class TileMap : public sf::Drawable, public sf::Transformable {
    public:
        TileMap(std::shared_ptr<sf::Texture> tileset);
        void loadFromArray(const int* map, uint width, uint height);
        void updateVertexArray();

    private:
        uint width;
        uint height;
        sf::VertexArray m_vertices;
        std::shared_ptr<sf::Texture> m_tileset;
        std::vector<std::unique_ptr<Tile>> m_tiles;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};