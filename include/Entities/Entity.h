#pragma once

#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <memory>

class TileMap; // Forward declaration

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(int id, std::shared_ptr<sf::Texture> texture, TileMap &tilemap);

    int getId() const { return id; }
    TileMap &getTileMap() const { return tilemap; }

    sf::Vector2i getGridPosition() const;
    void setGridPosition(const sf::Vector2i &pos);

    void setTexture(std::shared_ptr<sf::Texture> tex);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    int id;

    TileMap &tilemap;
    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> texture;
};