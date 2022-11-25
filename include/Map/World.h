#pragma once

#include "Entities/Character.h"
#include "Entities/Player.h"
#include "Map/TileMap.h"
#include "System/EntityManager.h"
#include "System/Resources/ResourceManager.h"

#include <SFML/Graphics.hpp>

class World : public sf::Drawable {
public:
	World(ResourceManager &resourceManager);

	void spawnPlayer();

	EntityManager<Character> &getCharacterManager() const { return *characterManager; }
	TileMap &getMap() const { return *tilemap; }
	Player &getPlayer() const { return *player; }
private:
	ResourceManager &resourceManager;

	std::unique_ptr<TileMap> tilemap;
	std::unique_ptr<Player> player;
	std::unique_ptr<EntityManager<Character>> characterManager;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};