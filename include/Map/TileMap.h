#pragma once

#include "Constants.h"
#include "Tile.h"
#include "System/EntityManager.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <nlohmann/json.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    explicit TileMap(std::shared_ptr<sf::Texture> tileset);

    void loadFromArray(const char *map, unsigned int _width, unsigned int _height);
    void loadFromFile(const std::string &mapName);

    void updateVertexArray();

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
    size_t getVertices() const { return vertices.getVertexCount(); }

    EntityManager &getEntityManager() const { return *entityManager; }
    Tile &getTile(sf::Vector2i pos) const;
    bool canWalk(sf::Vector2i pos) const;

private:
    unsigned int width;
    unsigned int height;

    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> tileset;
    std::vector<std::unique_ptr<Tile>> tiles;

    std::unique_ptr<EntityManager> entityManager;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};