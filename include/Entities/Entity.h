#pragma once

#include "Constants.h"
#include "System/ResourceManager.h"

#include <SFML/Graphics.hpp>

class TileMap; // Forward declaration

// TODO: Pass texture shared_ptr instead of ResourceManager?
// TODO: New Character and GroundItem classes?
class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(int id, const std::string &textureName, ResourceManager &resourceManager, TileMap &tilemap);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    int getId() const { return id; }
    TileMap &getTileMap() const { return tilemap; }

    sf::Vector2i getGridPosition() const;
    void setGridPosition(const sf::Vector2i &pos);

protected:
    int id;

    ResourceManager &resourceManager;
    TileMap &tilemap;
    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> texture;
};