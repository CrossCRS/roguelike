#pragma once

#include "Entity.hpp"

class EntityManager {
    public:
        void insertEntity(std::shared_ptr<Entity> entity);
        std::shared_ptr<Entity> getEntity(int id);
        void removeEntity(std::shared_ptr<Entity> entity);
        void removeEntity(int id);

        int count();
    private:
        std::unordered_map<int, std::shared_ptr<Entity>> m_entities;
};