#pragma once

#include "Constants.h"
#include "System/ResourceManager.h"

#include <SFML/Graphics.hpp>

class TileMap; // Forward declaration

// TODO: Pass texture shared_ptr instead of ResourceManager?
class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(int id, const std::string &textureName, ResourceManager &resourceManager, TileMap &tilemap);

    int getId() const { return id; }
    void setId(int _id) { id = _id; }

    TileMap& getTileMap() const { return tilemap; }

    bool isDimmed() const { return dimmed; }
    void setDimmed(bool _dimmed) {
        dimmed = _dimmed;

        // Might be useful for FOV? Eventually...
        if (dimmed) {
            vertices[0].color = sf::Color(64, 64, 64);
            vertices[1].color = sf::Color(64, 64, 64);
            vertices[2].color = sf::Color(64, 64, 64);
            vertices[3].color = sf::Color(64, 64, 64);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector2i getGridPosition() const;
    void setGridPosition(const sf::Vector2i &pos);
    void setGridPosition(int x, int y);

protected:
    int id;
    bool dimmed;

    ResourceManager &resourceManager;
    TileMap &tilemap;
    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> texture;
};