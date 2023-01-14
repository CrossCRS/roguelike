#pragma once

#include "Entities/Entity.h"
#include "Item.h"

class GroundItem : public Entity {
public:
    GroundItem(int id, std::unique_ptr<Item> _item, World &world) :
            Entity(id, _item->getTexture(), world),
            item(std::move(_item)) {}

private:
    std::unique_ptr<Item> item;
};