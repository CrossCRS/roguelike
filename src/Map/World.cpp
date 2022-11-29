#include "Map/World.h"

World::World(ResourceManager &resourceManager) : resourceManager(resourceManager) {
	tilemap = std::make_unique<TileMap>(nullptr);
	monsterManager = std::make_unique<EntityManager<Monster>>();
}

void World::spawnPlayer() {
	player = std::make_unique<Player>(0, resourceManager.getTexture("player"), *this);
	player->setGridPosition(tilemap->getPlayerSpawnPoint());
    player->setSpeed(1.0f);
    player->setCanInteractWithObjects(true);

    // TODO: Rebalance attributes?
    player->setBaseAttribute(Attribute::HEALTH, 10);
    player->setCurrentAttribute(Attribute::HEALTH, 10);
    player->setBaseAttribute(Attribute::STRENGTH, 10);
    player->setCurrentAttribute(Attribute::STRENGTH, 10);
}

Monster &World::spawnMonster(const std::string &name, const sf::Vector2i &pos) {
    auto monster = MonsterFactory::instantiate(name, *this);
    int id = monster->getId();
    monster->setGridPosition(pos);
    monsterManager->insertEntity(std::move(monster));

    return monsterManager->getEntity(id);
}

BaseTile &World::getTile(const sf::Vector2i &pos) const {
    return tilemap->getTile(pos);
}

Monster *World::getMonsterOnPos(const sf::Vector2i &pos) const {
    Monster *monster = nullptr;
    for (const auto &[id, m] : getMonsterManager().getAllEntities()) {
        if (m->getGridPosition() == pos) {
            monster = m.get();
        }
    }
    return monster;
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// Draw map
	target.draw(*tilemap, states);

	// Draw monsters
	for (auto const &element : monsterManager->getAllEntities()) {
		target.draw(*element.second, states);
	}

	// Draw player
	target.draw(*player, states);
}
