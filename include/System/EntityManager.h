#pragma once

#include "Entities/Entity.h"

#include <concepts>
#include <unordered_map>
#include <spdlog/spdlog.h>

template<std::derived_from<Entity> T>
class EntityManager {
public:
    EntityManager() = default;

    void insertEntity(std::unique_ptr<T> entity) {
        spdlog::debug("Adding entity {}", entity->getId());

        if (entities.contains(entity->getId())) {
            const auto message = "Entity with id " + std::to_string(entity->getId()) + " already exists";
            spdlog::error(message);
            throw std::invalid_argument(message);
        }

        entities.emplace(entity->getId(), std::move(entity));
    }

    T &getEntity(int id) const {
        if (!entities.contains(id)) {
            const auto message = "Entity with id " + std::to_string(id) + " doesn't exist";
            spdlog::error(message);
            throw std::invalid_argument(message);
        }
        
        return *(entities.find(id)->second);
    }

    void removeEntity(const T &entity) {
        removeEntity(entity.getId());
    }

    void removeEntity(int id) {
        if (!entities.contains(id)) {
            const auto message = "Entity with id " + std::to_string(id) + " doesn't exist";
            spdlog::error(message);
            throw std::invalid_argument(message);
        }

        entities.erase(id);
    }

    const std::unordered_map<int, std::unique_ptr<T>> &getAllEntities() const {
        return entities;
    }
    size_t count() const {
        return entities.size();
    }

private:
    std::unordered_map<int, std::unique_ptr<T>> entities;
};