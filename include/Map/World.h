#pragma once

#include "Entities/GroundItem.h"
#include "Entities/Monster.h"
#include "System/EntityManager.h"

#include <SFML/Graphics.hpp>

class BaseTile;
class MapGenerator;
class Player;
class ResourceManager;
class TileMap;

class World : public sf::Drawable {
public:
	World(ResourceManager &resourceManager);
    ~World() override;

	void generateFloor(unsigned int level);

	void spawnPlayer();
    Monster &spawnMonster(const std::string &name, const sf::Vector2i &pos);
    GroundItem &spawnGroundItem(const std::string &name, const sf::Vector2i &pos);
	void removeMonster(int id);

    BaseTile &getTile(const sf::Vector2i &pos) const;
    Monster *getMonsterOnPos(const sf::Vector2i &pos) const;
    Entity *getEntityOnPos(const sf::Vector2i &pos) const;

	EntityManager<Monster> &getMonsterManager() const { return *monsterManager; }
    EntityManager<Entity> &getEntityManager() const { return *entityManager; }
	TileMap &getMap() const { return *tilemap; }
	Player *getPlayer() const { return player.get(); }
	ResourceManager &getResourceManager() const { return resourceManager; }

	void update();

private:
	ResourceManager &resourceManager;

	std::unique_ptr<TileMap> tilemap;
	std::unique_ptr<Player> player;
	std::unique_ptr<EntityManager<Monster>> monsterManager; // Monster entities
    std::unique_ptr<EntityManager<Entity>> entityManager; // Other drawable entities
	std::unique_ptr<MapGenerator> mapGenerator;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::Vector2i getRandomWalkablePos();
};