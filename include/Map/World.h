#pragma once

#include "Entities/Monster.h"
#include "System/EntityManager.h"

#include <SFML/Graphics.hpp>

class BaseTile;
class Player;
class ResourceManager;
class TileMap;

class World : public sf::Drawable {
public:
	World(ResourceManager &resourceManager);

	void spawnPlayer();
    Monster &spawnMonster(const std::string &name, const sf::Vector2i &pos);

    BaseTile &getTile(const sf::Vector2i &pos) const;
    Monster *getMonsterOnPos(const sf::Vector2i &pos) const;

	EntityManager<Monster> &getMonsterManager() const { return *monsterManager; }
	TileMap &getMap() const { return *tilemap; }
	Player &getPlayer() const { return *player; }
	ResourceManager &getResourceManager() const { return resourceManager; }

private:
	ResourceManager &resourceManager;

	std::unique_ptr<TileMap> tilemap;
	std::unique_ptr<Player> player;
	std::unique_ptr<EntityManager<Monster>> monsterManager;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};