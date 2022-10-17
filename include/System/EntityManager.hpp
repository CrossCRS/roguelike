#pragma once
#include "Entities/Entity.hpp"

class EntityManager {
    public:
        void insertEntity(std::shared_ptr<Entity> entity);
        std::shared_ptr<Entity> getEntity(int id) const;
        void removeEntity(const std::shared_ptr<Entity>& entity);
        void removeEntity(int id);

        const std::unordered_map<int, std::shared_ptr<Entity>>& getAllEntities() const;

        size_t count();
    private:
        std::unordered_map<int, std::shared_ptr<Entity>> m_entities;
};