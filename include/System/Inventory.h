#pragma once

#include "Item.h"

class Character;

class Inventory {
public:
    Inventory(Character &_owner, size_t _size) : owner(_owner), size(_size) {}

    size_t getItemCount() const;

    size_t getSize() const;
    void setSize(size_t _size);

    Item &getItem(size_t pos);
    void addItem(std::unique_ptr<Item> item);
private:
    Character &owner;

    std::vector<std::unique_ptr<Item>> items;

    size_t size;
};