#include "Map/World.h"

#include "Entities/Monster.h"
#include "Entities/Player.h"
#include "Map/TileMap.h"
#include "Map/MapGenerator.h"
#include "System/EntityManager.h"
#include "System/Factories/ItemFactory.h"
#include "System/Factories/MonsterFactory.h"
#include "System/Resources/ResourceManager.h"

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

World::World(ResourceManager &resourceManager) : resourceManager(resourceManager) {
	tilemap = std::make_unique<TileMap>(nullptr);
	monsterManager = std::make_unique<EntityManager<Monster>>();
    entityManager = std::make_unique<EntityManager<Entity>>();
    mapGenerator = std::make_unique<MapGenerator>();
}
World::~World() = default;

void World::generateFloor(unsigned /*level*/) {
    const auto [map, w, h, spawnPos] = mapGenerator->generate();
    tilemap->loadFromArray(map.data(), w, h);

    // TODO: Spawn exit

    // Monsters (TODO: diffrent monsters depending on level)
    auto monsterCount = Random::get<int>(15, 35);
    for (int i = 0; i < monsterCount; i++) {
        // TODO: Rewrite!!!
        spawnMonster(Random::get({ "rat", "rat", "rat", "rat", "rat", "goblin" }), getRandomWalkablePos());
    }

    // Items
    auto itemCount = Random::get<int>(2, 6);
    for (int i = 0; i < itemCount; i++) {
        spawnGroundItem("butter_knife", getRandomWalkablePos());
    }
    
    tilemap->setPlayerSpawnPoint(spawnPos);
}

void World::spawnPlayer() {
	player = std::make_unique<Player>(0, resourceManager.getTexture("player"), *this);
	player->setGridPosition(tilemap->getPlayerSpawnPoint());
}

Monster &World::spawnMonster(const std::string &name, const sf::Vector2i &pos) {
    auto monster = MonsterFactory::instantiate(name, *this);
    int id = monster->getId();
    monster->setGridPosition(pos);
    monsterManager->insertEntity(std::move(monster));

    return monsterManager->getEntity(id);
}

GroundItem &World::spawnGroundItem(const std::string &name, const sf::Vector2i &pos) {
    auto item = ItemFactory::instantiate(name, *this);
    int id = item->getId();

    std::unique_ptr<GroundItem> groundItem = std::make_unique<GroundItem>(id, std::move(item), *this);
    groundItem->setGridPosition(pos);
    entityManager->insertEntity(std::move(groundItem));

    return dynamic_cast<GroundItem&>(entityManager->getEntity(id));
}

void World::removeMonster(int id) {
    monsterManager->removeEntity(id);
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

Entity *World::getEntityOnPos(const sf::Vector2i &pos) const {
    Entity *entity = nullptr;
    for (const auto &[id, e] : getEntityManager().getAllEntities()) {
        if (e->getGridPosition() == pos) {
            entity = e.get();
        }
    }
    return entity;
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// Draw map
	target.draw(*tilemap, states);

    // Draw entities
    for (auto const &element : getEntityManager().getAllEntities()) {
        target.draw(*element.second, states);
    }

	// Draw monsters
	for (auto const &element : getMonsterManager().getAllEntities()) {
		target.draw(*element.second, states);
	}

	// Draw player
	target.draw(*player, states);
}

void World::update() {
    for (auto const &element : getEntityManager().getAllEntities()) {
        element.second->update();
    }

    for (auto const &element : getMonsterManager().getAllEntities()) {
        element.second->update();
    }

    player->update();
}

sf::Vector2i World::getRandomWalkablePos() {
    int x, y;
    do {
        x = Random::get<int>(0, tilemap->getWidth() - 1);
        y = Random::get<int>(0, tilemap->getHeight() - 1);
    } while (tilemap->getTile(x, y)->isImpenetrable());
    return { x, y };
}
