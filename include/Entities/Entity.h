#pragma once

#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <memory>

class World; // Forward declaration

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(int id, std::shared_ptr<sf::Texture> texture, World &world);

    int getId() const { return id; }
    World &getWorld() const { return world; }

    sf::Vector2i getGridPosition() const;
    void setGridPosition(const sf::Vector2i &pos);

    void setTexture(std::shared_ptr<sf::Texture> tex);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    int id;

    World &world;
    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> texture;
};