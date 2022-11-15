#pragma once

#include "Entities/Entity.h"

#include <unordered_map>

class EntityManager {
public:
    EntityManager() = default;

    void insertEntity(std::shared_ptr<Entity> entity);

    std::shared_ptr<Entity> getEntity(int id) const;

    void removeEntity(const std::shared_ptr<Entity> &entity);
    void removeEntity(int id);

    const std::unordered_map<int, std::shared_ptr<Entity>> &getAllEntities() const;
    size_t count() const;

private:
    std::unordered_map<int, std::shared_ptr<Entity>> entities;
};