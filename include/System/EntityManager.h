#pragma once

#include "Entities/Entity.h"

#include <concepts>
#include <unordered_map>
#include <spdlog/spdlog.h>

template<std::derived_from<Entity> T>
class EntityManager {
public:
    EntityManager() = default;

    void insertEntity(std::shared_ptr<T> entity) {
        auto it = entities.find(entity->getId());

        spdlog::debug("Adding entity {}", entity->getId());

        if (it != entities.end()) {
            const auto message = "Entity with id " + std::to_string(it->first) + " already exists";
            spdlog::error(message);
            throw std::invalid_argument(message);
        }

        entities.emplace(entity->getId(), std::move(entity));
    }

    std::shared_ptr<T> getEntity(int id) const {
        auto it = entities.find(id);

        if (it == entities.end()) {
            return nullptr;
        }

        return it->second;
    }

    void removeEntity(const std::shared_ptr<T> &entity) {
        removeEntity(entity->getId());
    }

    void removeEntity(int id) {
        auto it = entities.find(id);

        if (it == entities.end()) {
            const auto message = "Entity with id " + std::to_string(id) + " doesn't exist";
            spdlog::error(message);
            throw std::invalid_argument(message);
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