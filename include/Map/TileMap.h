#pragma once

#include "Constants.h"
#include "Entities/Character.h"
#include "Map/Tiles/BaseTile.h"
#include "Map/Tiles/DoorTile.h"
#include "Map/Tiles/FloorTile.h"
#include "Map/Tiles/WallTile.h"
#include "System/EntityManager.h"

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

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
    
    BaseTile &getTile(sf::Vector2i pos) const;

private:
    unsigned int width;
    unsigned int height;

    sf::Vector2i playerSpawnPoint;

    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> tileset;
    std::vector<std::unique_ptr<BaseTile>> tiles;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};