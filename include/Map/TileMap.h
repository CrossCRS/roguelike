#pragma once

#include "Tiles/BaseTile.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    explicit TileMap(std::shared_ptr<sf::Texture> tileset) : tileset(std::move(tileset)) {}

    void loadFromArray(const char *map, unsigned int _width, unsigned int _height);
    void loadFromFile(const std::string &mapName);

    void updateVertexArray();

    const sf::Vector2i &getPlayerSpawnPoint() const { return playerSpawnPoint; }
    void setPlayerSpawnPoint(const sf::Vector2i &spawnPoint);

    void setTileset(std::shared_ptr<sf::Texture> _tileset);

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
    size_t getVerticesCount() const { return vertices.getVertexCount(); }
    
    BaseTile &getTile(const sf::Vector2i &pos) const;
    BaseTile *getTile(unsigned int x, unsigned int y) const;

private:
    unsigned int width;
    unsigned int height;

    sf::Vector2i playerSpawnPoint;

    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> tileset;
    std::vector<std::unique_ptr<BaseTile>> tiles;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};