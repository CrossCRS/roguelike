#pragma once

#include "Entities/Entity.h"

#include <unordered_map>

template<typename T>
class EntityManager {
public:
    EntityManager() = default;

    void insertEntity(std::shared_ptr<T> entity) {
        auto it = entities.find(entity->getId());

        if (it != entities.end()) {
            throw std::invalid_argument("Entity with given id already exists");
        }

        entities.emplace(entity->getId(), std::move(entity));
    }

    std::shared_ptr<T> getEntity(int id) const {
        auto it = entities.find(id);

        if (it == entities.end()) {
            throw std::invalid_argument("Entity with given id doesn't exist");
        }

        return it->second;
    }

    void removeEntity(const std::shared_ptr<T> &entity) {
        removeEntity(entity->getId());
    }

    void removeEntity(int id) {
        auto it = entities.find(id);

        if (it == entities.end()) {
            throw std::invalid_argument("Entity with given id doesn't exist");
        }

        entities.erase(id);
    }

    const std::unordered_map<int, std::shared_ptr<T>> &getAllEntities() const {
        return entities;
    }
    size_t count() const {
        return entities.size();
    }

private:
    std::unordered_map<int, std::shared_ptr<T>> entities;
};