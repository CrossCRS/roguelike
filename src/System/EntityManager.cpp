#include "System/EntityManager.h"

void EntityManager::insertEntity(std::shared_ptr<Entity> entity) {
    auto it = entities.find(entity->getId());

    if (it != entities.end()) {
        throw std::invalid_argument("Entity with given id already exists");
    }

    entities.emplace(entity->getId(), std::move(entity));
}

std::shared_ptr<Entity> EntityManager::getEntity(int id) const {
    auto it = entities.find(id);

    if (it == entities.end()) {
        throw std::invalid_argument("Entity with given id doesn't exist");
    }

    return it->second;
}

void EntityManager::removeEntity(const std::shared_ptr<Entity> &entity) {
    removeEntity(entity->getId());
}

void EntityManager::removeEntity(int id) {
    auto it = entities.find(id);

    if (it == entities.end()) {
        throw std::invalid_argument("Entity with given id doesn't exist");
    }

    entities.erase(id);
}

size_t EntityManager::count() {
    return entities.size();
}

const std::unordered_map<int, std::shared_ptr<Entity>> &EntityManager::getAllEntities() const {
    return entities;
}