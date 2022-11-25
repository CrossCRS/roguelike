#include "Map/World.h"

World::World(ResourceManager &resourceManager) : resourceManager(resourceManager) {
	tilemap = std::make_unique<TileMap>(nullptr);
	characterManager = std::make_unique<EntityManager<Character>>();
}

void World::spawnPlayer() {
	player = std::make_unique<Player>(0, resourceManager.getTexture("player"), *this);
	player->setGridPosition(tilemap->getPlayerSpawnPoint());
}


void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// Draw map
	target.draw(*tilemap, states);

	// Draw entities
	for (auto const &element : characterManager->getAllEntities()) {
		target.draw(*element.second, states);
	}

	// Draw player
	target.draw(*player, states);
}
