#pragma once

#include "Constants.h"
#include "Map/Tiles/BaseTile.h"
#include "Map/Tiles/DoorTile.h"
#include "Map/Tiles/FloorTile.h"
#include "Map/Tiles/WallTile.h"
#include "System/EntityManager.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    explicit TileMap(std::shared_ptr<sf::Texture> tileset);

    void loadFromArray(const char *map, unsigned int _width, unsigned int _height);
    void loadFromFile(const std::string &mapName);

    void updateVertexArray();

    const sf::Vector2i &getPlayerSpawnPoint() const { return playerSpawnPoint; }
    void setPlayerSpawnPoint(const sf::Vector2i &spawnPoint);

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
    size_t getVerticesCount() const { return vertices.getVertexCount(); }

    EntityManager &getEntityManager() const { return *entityManager; }
    BaseTile &getTile(sf::Vector2i pos) const;

private:
    unsigned int width;
    unsigned int height;

    sf::Vector2i playerSpawnPoint;

    sf::VertexArray vertices;
    std::shared_ptr<sf::Texture> tileset;
    std::vector<std::unique_ptr<BaseTile>> tiles;

    std::unique_ptr<EntityManager> entityManager;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};