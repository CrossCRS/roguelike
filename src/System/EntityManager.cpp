#include "System/EntityManager.h"

void EntityManager::insertEntity(std::shared_ptr<Entity> entity) {
    auto it = m_entities.find(entity->getId());

    if (it != m_entities.end()) {
        throw std::invalid_argument("Entity with given id already exists");
    }

    m_entities.emplace(entity->getId(), std::move(entity));
}

std::shared_ptr<Entity> EntityManager::getEntity(int id) const {
    auto it = m_entities.find(id);

    if (it == m_entities.end()) {
        throw std::invalid_argument("Entity with given id doesn't exist");
    }

    return it->second;
}

void EntityManager::removeEntity(const std::shared_ptr<Entity> &entity) {
    removeEntity(entity->getId());
}

void EntityManager::removeEntity(int id) {
    auto it = m_entities.find(id);

    if (it == m_entities.end()) {
        throw std::invalid_argument("Entity with given id doesn't exist");
    }

    m_entities.erase(id);
}

size_t EntityManager::count() {
    return m_entities.size();
}

const std::unordered_map<int, std::shared_ptr<Entity>> &EntityManager::getAllEntities() const {
    return m_entities;
}